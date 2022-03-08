# Not Mini Shell

일단 현재 파싱을 단어 단위로 하고 있습니다.

ex) echo "hello world" | wc -l > outfile -> ["echo", "hello world", "|", "wc", "-l", ">", "outfile"]
    < infile cat | wc -l -> ["<", "infile", ...]

아직 fd를 추가하거나 다른 기능은 넣지 않았습니다.

make debug를 실행하면 일단 제가 코딩한 소스들만 debug 할 수 있게 컴파일하는 make 규칙을 넣었습니다.