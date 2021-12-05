build_frontend:
	./scripts/builder.sh --frontend

dev_build_frontend:
	cd web && npm run-script start

build_backend:
	./scripts/builder.sh --backend

backend: build_backend
	./build/server

clean:
	rm -rf build
	mkdir build

.PHONY: build clean