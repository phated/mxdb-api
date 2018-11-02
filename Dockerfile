FROM node:alpine

WORKDIR /server

COPY ./package.json /server/
COPY ./npm-shrinkwrap.json /server/

RUN npm install

COPY . /server/

CMD ["npm", "start"]
