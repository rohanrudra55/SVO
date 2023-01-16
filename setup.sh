NEXT=1
while ((NEXT))
    do
        folder=build
        [ -d "$folder" ] && echo "Folder exists!" || mkdir "$folder"
        cd build
        cmake ..
        make
        ./output -h
        # ./output
        echo "CLEAN (Y/N)?"
        read op
        op=$(echo $op | tr 'a-z' 'A-Z')
        if [ $op = "Y" ];then
            rm -r ./output 
            cd ..
            rm -r build
            NEXT=0
        fi
        cd ..
    shift
done