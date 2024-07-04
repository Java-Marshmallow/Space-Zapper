emcc -o SpaceZapperGame.html ./scripts/main.cpp ./scripts/bullet.cpp ./scripts/cursor.cpp ./scripts/enemy.cpp ./scripts/player.cpp ./scripts/textBox.cpp -Os -Wall /home/aedan/raylib/src/web/libraylib.a -I. -I/home/aedan/raylib/src/ -I./headers -L. -L/home/aedan/raylib/src/web/libraylib.a -s USE_GLFW=3 -s ASYNCIFY --shell-file /home/aedan/raylib/src/shell.html -DPLATFORM_WEB --preload-file ./assets -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=0 -s FORCE_FILESYSTEM=0 -s ASSERTIONS=1 --profiling -s ERROR_ON_UNDEFINED_SYMBOLS=0 && python3 -m http.server 8080

