build:
	docker build -t backend:1 --file ./foxgres/Dockerfile .
	docker build -t migrate:1 --file ./migrate/Dockerfile .
	docker build -t frontend:1 --file ./foxgres-ui/Dockerfile .
	docker-compose build
run: build
	docker-compose up -d
stop:
	docker-compose down