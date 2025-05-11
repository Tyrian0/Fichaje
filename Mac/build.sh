#!/usr/bin/env bash
set -euo pipefail

# Ruta al directorio raíz del proyecto
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
APP_DIR="$ROOT_DIR/../app"
BUILD_DIR="$ROOT_DIR/../build"
BUILD_TYPE=${BUILD_TYPE:-Release}

function configure() {
  echo "==> Creando directorio de build y configurando CMake"
  mkdir -p "$BUILD_DIR"
  cmake -S "$APP_DIR" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
}

function build() {
  echo "==> Compilando en modo $BUILD_TYPE"
  cmake --build "$BUILD_DIR" --config "$BUILD_TYPE"
}

function clean() {
  echo "==> Limpiando build"
  rm -rf "$BUILD_DIR"
}

function usage() {
  cat <<EOF
Usage: $(basename "$0") [command]

Commands:
  configure   Genera los ficheros de build con CMake (fuente en app/)
  build       Compila (requiere configure previo)
  clean       Elimina build/
  rebuild     clean + configure + build
  all         configure + build   (por defecto si no pones nada)
EOF
  exit 1
}

CMD=${1:-all}
case "$CMD" in
  configure)  configure     ;;
  build)      build         ;;
  clean)      clean         ;;
  rebuild)    clean && configure && build ;;
  all)        configure && build        ;;
  *)          usage         ;;
esac
