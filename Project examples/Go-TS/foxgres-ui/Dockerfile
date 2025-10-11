FROM node:14

WORKDIR /usr/src/app
COPY ./foxgres-ui/package*.json ./
RUN npm install
COPY ./foxgres-ui ./

EXPOSE 5173

CMD [ "npm", "run", "dev" ]