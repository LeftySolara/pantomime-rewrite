find . -iname "*.c" | xargs clang-format -style=file -i
mkdir -p build
gcc src/pantomime.c src/mpdwrapper.c -lmpdclient -Wall -Werror -g -O0 -o build/pantomime
