FROM node:18

WORKDIR /app

COPY package.json yarn.lock .

RUN yarn --immutable

COPY . .

ENV ADMIN=1c78d6cbeb7f3314df4d4fbd960acd3b

CMD ["node", "source/index.js"]
