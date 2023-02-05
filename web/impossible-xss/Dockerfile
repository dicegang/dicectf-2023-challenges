FROM node:18

WORKDIR /app
COPY package.json .
RUN npm i

COPY app.js ./

USER node
CMD node app.js
