#!/bin/bash
for source in ./*.rinha; do
    filename="${source##*/}"
    filename="${filename%.*}"
    echo "$filename".json
    rinha $source >  "$filename".json

    ## Chamada no CMakeList
    #echo "add_test(NAME test_"$filename" COMMAND interpreter_test \"test_"$filename"\" \"\${CMAKE_SOURCE_DIR}/tests/test_data/"$filename".json\")"
    
    ## Declaração na classe
    #echo "void test_"$filename"(File);"

    ## Verificar qual teste chamar
    #echo "else if(test_name == \"test_"$filename"\")"
    #echo "    test_"$filename"(file);"


    ## Método de assert
    # echo "void test_"$filename"(File file){"
    # echo "    auto expected = \"\";"
    # echo ""
    # echo "    interpreter::walk(file);"
    # echo ""
    # echo "    assert(oss && oss.str() == expected);"
    # echo "}"

done