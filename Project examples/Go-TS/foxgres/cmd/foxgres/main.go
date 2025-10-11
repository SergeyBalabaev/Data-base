package main

import (
	"context"
	"fmt"
	"log"
	"os"

	"github.com/jackc/pgx/v5"
	"github.com/labstack/echo/v4"
	"github.com/labstack/echo/v4/middleware"
	echoSwagger "github.com/swaggo/echo-swagger"

	_ "foxgres/cmd/foxgres/docs"
	"foxgres/cmd/foxgres/handler"
	"foxgres/internal/config"
	"foxgres/internal/service"
	"foxgres/internal/storage"
)

//	@title			foxgres API
//	@version		0.1.0
//	@description	Ориокс здорового человека

//	@host		localhost:8080
//
// nolint:funlen
func main() {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	cfg := config.NewFoxgresConfig()

	name := os.Getenv("PG_NAME")
	user := os.Getenv("PG_USER")
	pass := os.Getenv("PG_PASSWORD")
	host := os.Getenv("PG_HOST")

	url := fmt.Sprintf("postgres://%s:%s@%s:5432/%s", user, pass, host, name)

	conn, err := pgx.Connect(ctx, url)
	if err != nil {
		log.Fatalf(err.Error())
	}
	err = conn.Ping(ctx)
	if err != nil {
		log.Printf(err.Error())
	}
	defer func() { _ = conn.Close(ctx) }()

	userStorage := storage.NewUserStorage(conn)
	fieldStorage := storage.NewFieldStorage(conn)
	studentStorage := storage.NewStudentStorage(conn)
	foxgresService := service.NewService(userStorage, fieldStorage, studentStorage)
	foxgresHandler := handler.NewHandler(foxgresService)

	e := echo.New()

	e.Use(middleware.CORS())

	e.GET("/auth", foxgresHandler.Auth)
	e.GET("/marks", foxgresHandler.Marks)
	e.GET("/docs/*", echoSwagger.WrapHandler)

	log.Fatal(e.Start(cfg.ListenAddr))
}
