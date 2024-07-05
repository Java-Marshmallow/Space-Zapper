cd ../ && emcc -o index.html ./scripts/main.cpp ./scripts/bullet.cpp ./scripts/cursor.cpp ./scripts/enemy.cpp ./scripts/player.cpp ./scripts/textBox.cpp -Os -Wall $HOME/raylib/src/web/libraylib.a -I. -I$HOME/raylib/src/ -I./headers -L. -L$HOME/raylib/src/web/libraylib.a -s USE_GLFW=3 -s ASYNCIFY --shell-file $HOME/Documents/SpaceZapper/web_build/SZShell.html -DPLATFORM_WEB --preload-file ./assets -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=0 -s FORCE_FILESYSTEM=0 -s ASSERTIONS=1 --profiling -s ERROR_ON_UNDEFINED_SYMBOLS=0 && python3 -m http.server 8080

