
int main()
{
    foobar_lib = dlopen("./libfoo.so", RTLD_LAZY | RTLD_DEEPBIND);

    fooInt = reinterpret_cast<foo_int>(dlsym(foobar_lib, "_Z3Fooi"));
    fooChar = reinterpret_cast<foo_char>(dlsym(foobar_lib, "_Z3Fooc"));
    
    fooInt(5);
    fooChar('5');

    dlclose(foobar_lib);
    
    return 0;
}
