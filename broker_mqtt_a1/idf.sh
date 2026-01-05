#!/usr/bin/env bash
set -euo pipefail

# ---- Config ----
IDF_PATH_DEFAULT="/l/disk0/josemar/development/pessoal/curso-iot/esp32/esp-idf"
BAUD_DEFAULT="115200"

usage() {
  cat <<EOF
Uso:
  ./idf.sh <cmd> [opções]

Comandos longos:
  fullclean   -> idf.py fullclean
  clean       -> idf.py clean
  build       -> idf.py build
  flash       -> idf.py flash
  monitor     -> idf.py monitor
  flashmon    -> build + flash + monitor
  all         -> fullclean + build + flash

Comandos curtos:
  bb          -> build
  bf          -> build + flash
  bfm         -> build + flash + monitor
  ball        -> fullclean + build + flash

Opções:
  -p, --port  <PORT>   Porta serial (ex: /dev/ttyUSB0 ou /dev/serial/by-id/...)
  -b, --baud  <BAUD>   Baudrate (default: 115200)
  --idf       <PATH>   Caminho do esp-idf

Exemplos:
  ./idf.sh bb
  ./idf.sh bf
  ./idf.sh bfm
  ./idf.sh ball -p /dev/serial/by-id/usb-XXXX
EOF
}

detect_port() {
  if compgen -G "/dev/serial/by-id/*" > /dev/null; then
    ls -1 /dev/serial/by-id/* | head -n 1
    return
  fi
  if compgen -G "/dev/ttyUSB*" > /dev/null; then
    ls -1 /dev/ttyUSB* | head -n 1
    return
  fi
  if compgen -G "/dev/ttyACM*" > /dev/null; then
    ls -1 /dev/ttyACM* | head -n 1
    return
  fi
  echo ""
}

# ---- Args ----
CMD="${1:-}"
shift || true

IDF_PATH="$IDF_PATH_DEFAULT"
PORT=""
BAUD="$BAUD_DEFAULT"

while [[ $# -gt 0 ]]; do
  case "$1" in
    -p|--port) PORT="$2"; shift 2;;
    -b|--baud) BAUD="$2"; shift 2;;
    --idf) IDF_PATH="$2"; shift 2;;
    -h|--help) usage; exit 0;;
    *) echo "Arg inválido: $1"; usage; exit 1;;
  esac
done

[[ -z "$CMD" ]] && usage && exit 1

# ---- Load ESP-IDF ----
if [[ ! -f "$IDF_PATH/export.sh" ]]; then
  echo "ERRO: export.sh não encontrado em $IDF_PATH"
  exit 1
fi

# shellcheck disable=SC1090
source "$IDF_PATH/export.sh" >/dev/null

# ---- Porta ----
if [[ -z "$PORT" ]]; then
  PORT="$(detect_port)"
  [[ -z "$PORT" ]] && echo "Porta não encontrada, use -p" && exit 1
fi

echo "▶ CMD   : $CMD"
echo "▶ PORT  : $PORT"
echo "▶ BAUD  : $BAUD"
echo "▶ IDF   : $IDF_PATH"
echo

run() {
  echo "+ idf.py -p \"$PORT\" -b \"$BAUD\" $*"
  idf.py -p "$PORT" -b "$BAUD" "$@"
}

case "$CMD" in
  # ---- curtos ----
  bb)
    run build
    ;;
  bf)
    run build
    run flash
    ;;
  bfm)
    run build
    run flash
    run monitor
    ;;
  ball)
    run fullclean
    run build
    run flash
    ;;

  # ---- longos ----
  build)     run build ;;
  clean)     run clean ;;
  fullclean) run fullclean ;;
  flash)     run flash ;;
  monitor)   run monitor ;;
  flashmon)
    run build
    run flash
    run monitor
    ;;
  all)
    run fullclean
    run build
    run flash
    ;;
  *)
    echo "Comando inválido: $CMD"
    usage
    exit 1
    ;;
esac