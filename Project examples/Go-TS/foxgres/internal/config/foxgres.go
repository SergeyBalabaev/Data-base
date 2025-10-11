package config

type FoxgresConfig struct {
	ListenAddr string
}

func NewFoxgresConfig() *FoxgresConfig {
	return &FoxgresConfig{
		ListenAddr: ":8080",
	}
}
