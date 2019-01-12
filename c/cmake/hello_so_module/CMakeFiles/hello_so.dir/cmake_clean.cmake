FILE(REMOVE_RECURSE
  "CMakeFiles/hello_so.dir/main.c.o"
  "hello_so.pdb"
  "hello_so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/hello_so.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
