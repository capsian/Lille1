build_frontend:
	cd web/app && npm run build
	rm -rf build/web/*
	mv web/app/build/* build/web
	rm -rf web/app/build

dev_frontend:
	cd web/app && npm run-script start

build_backend:
	go build -v cmd/server.go
	mv server build

backend: build_backend
	./build/server

clean_tweet:
	go build -v cmd/clean_tweet.go
	mv clean_tweet build
	./build/clean_tweet

script_runner:
	go build -v cmd/script_runner.go
	mv script_runner build
	./build/script_runner

csv:
	go build cmd/csv.go
	mv csv build
	./build/csv

server:
	go build cmd/server.go
	mv server build
	./build/server

clean:
	rm -rf build
	mkdir build

.PHONY: build clean
