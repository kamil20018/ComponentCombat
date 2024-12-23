#! /bin/bash

thread_count=$(nproc --all)

while getopts 'brashcCfli' OPTION; do
    case "$OPTION" in
        h)
            echo "run - can set up the cmake project, build it and run it."
            echo ""
            echo "options:"
            echo "-h   show brief help"
            echo "-s   sets the cmake build and source directories"
            echo "-b   builds the project"
            echo "-r   runs the project"
            echo "-a   builds and runs the project"
            echo "-c   removes all of the build files"
            echo "-l   get line count"
            echo "-f   format files"
            echo "-i   generate image file"
            ;;
        s)
            mkdir build
            cmake -S . -B build
            ;;
        b)
            cd build
            time cmake --build . -- -j $thread_count
            ;;
        r)
            cd build
            ./bin/game
            ;;
        a) 
            cd build
            time cmake --build . -- -j $thread_count
            if [ $? -eq 0 ]; then #only runs the game if the build succeeded
                ./bin/game
            fi
            ;;
        c)
            rm -rf build/src
            ;;
        C)
            rm -rf build
            ;;
        l)
            cloc --exclude-dir=imgui src/
            ;;
        f)
            find src/ -iname '*.h*' -o -iname '*.cpp' | xargs clang-format -style=file -i
            ;;
        i)
            cd tools
            python3 gen_img.py  
            cd ..
    esac
done
