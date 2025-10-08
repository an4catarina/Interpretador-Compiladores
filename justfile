src_path := "interpretador"
build_path := "interpretador/build"

build:
    cmake -G Ninja -S {{ src_path }} -B {{ build_path }} -DCMAKE_BUILD_TYPE=Debug
    ninja -C {{ build_path }}

test cases="test": build
    pytest -k {{ cases }} interpretador/test 

clean:
    rm -rf {{ build_path }}

run file="":
    ./{{ build_path }}/interpretador {{ if file != "" { prepend("< ", file) } else { "" } }} 
    
