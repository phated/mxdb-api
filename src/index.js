import fetch from 'node-fetch';
import { ApolloServer } from 'apollo-server';
import { mergeSchemas, makeRemoteExecutableSchema, introspectSchema } from 'graphql-tools';
import { HttpLink } from 'apollo-link-http';

async function getRemoteSchema(uri, headers) {
  const link = new HttpLink({
    uri,
    fetch,
    headers
  });

  const schema = await introspectSchema(link);
  return makeRemoteExecutableSchema({
    schema,
    link
  });
};

async function createSchema() {
  async function publicDecksResolver(root, args, context, info) {
    const response = await fetch(`https://metax.toyboat.net/netdecker.php?json=true`);
    if (response.ok) {
      const decks = await response.json();
      return decks;
    } else {
      return [];
    }
  }

  async function deckResolver(root, args, context, info) {
    // console.log(arguments);
    const response = await fetch(`https://metax.toyboat.net/decodeDeck.php?output=metaxdb&hash=${args.hash}`);
    if (response.ok) {
      const cards = await response.json();
      return Object.keys(cards).map(uid => ({ uid: uid, quantity: cards[uid] }));
    } else {
      return [];
    }
  }

  function cardResolver(card, args, context, info) {
    return info.mergeInfo.delegateToSchema({
      schema: graphcoolSchema,
      operation: 'query',
      fieldName: 'Card',
      args: {
        uid: card.uid
      },
      context,
      info,
    });
  }

  function uidResolver(card, args, context, info) {
    return card.uid;
  }

  function quantityResolver(card, args, context, info) {
    return card.quantity || 0;
  }

  function authorResolver(deck, args, context, info) {
    return deck.author || "";
  }

  function nameResolver(deck, args, context, info) {
    return deck.name || "";
  }

  function dateResolver(deck, args, context, info) {
    if (deck.date) {
      return new Date(deck.date);
    } else {
      // TODO: Not sure I like this
      return new Date();
    }
  }

  function hashResolver(deck, args, context, info) {
    return deck.hash || "";
  }

  function sourceResolver(deck, args, context, info) {
    return deck.source || "";
  }

  const graphcoolSchema = await getRemoteSchema(
    "https://api.graph.cool/simple/v1/metaxdb"
  );

  const typeDefs = `
    type CardInDeck {
      id: ID!
      card: Card!
      quantity: Int!
    }

    type PublicDeck {
      author: String!
      name: String!
      date: DateTime!
      hash: String!
      source: String!
      deck: [CardInDeck]!
    }

    type Query {
      deck(hash: String!): [CardInDeck]!
      publicDecks: [PublicDeck]!
    }
  `;

  const resolvers = {
    CardInDeck: {
      id: uidResolver,
      card: cardResolver,
      quantity: quantityResolver
    },
    PublicDeck: {
      author: authorResolver,
      name: nameResolver,
      date: dateResolver,
      hash: hashResolver,
      source: sourceResolver,
      deck: (publicDeck, args, context, info) => deckResolver(undefined, publicDeck, context, info),
    },
    Query: {
      deck: deckResolver,
      publicDecks: publicDecksResolver,
    },
  };

  const finalSchema = mergeSchemas({
    schemas: [
      graphcoolSchema,
      typeDefs,
    ],
    resolvers,
  });

  return finalSchema;
}

function createServer(schema) {
  return new ApolloServer({
    schema,
    introspection: true,
    playground: true
  });
}

const runServer = async () => {
  const schema = await createSchema();

  const server = createServer(schema);

  const { url } = await server.listen({
    port: process.env.PORT || 4000
  });

  console.log('Server running. Open ' + url + ' to run queries.');
}

try {
  runServer();
} catch (e) {
  console.log(e, e.message, e.stack);
}
