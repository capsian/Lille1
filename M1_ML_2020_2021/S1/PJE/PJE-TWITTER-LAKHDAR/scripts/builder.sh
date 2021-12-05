#!/bin/bash

if [ ! -f "Makefile" ]; then
  echo "Please run the script with make"
  exit 1
fi

PROJECT_PATH=$(pwd)
BUILD_PATH="$PROJECT_PATH""/build/"
FRONTEND_BUILD_PATH="$PROJECT_PATH""/build/web/"

function frontend() {
  echo "Building Frontend"
  cd "$PROJECT_PATH" || exit 1
  cd web || exit 1
  #npm install
	npm run build
	rm -rf "$FRONTEND_BUILD_PATH" || true
  mkdir -p "$BUILD_PATH" "$FRONTEND_BUILD_PATH"
	mv -f build/* "$FRONTEND_BUILD_PATH"
	rm -rf build
}

function backend() {
  echo "Building Backend"
  cd "$PROJECT_PATH" || exit 1
  cd cmd || exit 1
  go build -o server server.go
  mkdir -p "$BUILD_PATH"
  mv server "$BUILD_PATH"
}


for i in "$@"; do
    case $i in
        --frontend) frontend; shift ;;
        --backend) backend; shift ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done



exit 0