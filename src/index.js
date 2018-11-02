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
  async function deckResolver(root, args, context, info) {
    const response = await fetch(`https://metax.toyboat.net/decodeDeck.php?output=metaxdb&hash=${args.hash}`);
    if (response.ok) {
      const cards = await response.json();
      return Object.keys(cards).map(uid => ({ uid: uid, quantity: cards[uid] }));
    } else {
      return null;
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

  function quantityResolver(card, args, context, info) {
    return card.quantity || 0;
  }

  const graphcoolSchema = await getRemoteSchema(
    "https://api.graph.cool/simple/v1/metaxdb"
  );

  const typeDefs = `
    type CardInDeck {
      card: Card!
      quantity: Int!
    }

    type Query {
      deck(hash: String!): [CardInDeck!]!
    }
  `;

  const resolvers = {
    CardInDeck: {
      card: cardResolver,
      quantity: quantityResolver
    },
    Query: {
      deck: deckResolver,
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
