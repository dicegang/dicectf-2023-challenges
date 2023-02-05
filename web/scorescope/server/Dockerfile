FROM node:18

WORKDIR /app

COPY package.json yarn.lock .

RUN yarn --immutable

COPY . .

ENV FLAG=dice{still_more_secure_than_gradescope}

CMD ["node", "index.js"]
