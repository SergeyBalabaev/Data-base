FROM golang:alpine AS build

WORKDIR /app

ENV GO111MODULE=on
COPY foxgres/go.mod foxgres/go.sum ./
RUN go mod download

COPY /foxgres/ ./
RUN go build -o main cmd/foxgres/main.go

EXPOSE 8080

FROM scratch

COPY --from=build app/main /bin/main

ENTRYPOINT ["/bin/main"]