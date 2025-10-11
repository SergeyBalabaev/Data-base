# :fox_face: Foxgres

## Quickstart

> *Notice: at first download requirements*

Clone repo

    git clone https://github.com/KeoFoxy/foxgres

Change directory

    cd foxgres

Run app in docker

    make run


## Frontend

* React
* TypeScript
* MUI
* Vite
* TBA...

### Requirements

* [Node.js](https://nodejs.org/en) | `brew install node`

How to run UI

```sh
npm install
npm run dev
```

## Backend

* Golang

Run backend with postgres in docker:

```sh
make run #run all containers
make stop #stop all containers
```

Swagger available on `http://localhost:8080/docs/`

pgAdmin available on `http://localhost:5050`

    login: admin@admin.com
    password: admin

    postgres_host: db
    postgres_database: foxgres
    postgres_password: admin

### Requirements

* [Go](https://go.dev/dl/) 
* [Docker](https://www.docker.com/products/docker-desktop/)

## Contributing 

**Branch naming**

```
frontend/your-feature
backend/your-feature
```