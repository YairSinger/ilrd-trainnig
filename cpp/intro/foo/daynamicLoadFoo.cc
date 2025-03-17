#include <iostream>
#include <dlfcn.h> // For dynamic loading

// Function pointer type for the function we want to call
typedef void (*FooFunction)();

int main() {
    // Load the shared library
    void* libraryHandle = dlopen("./foo.so", RTLD_NOW | RTLD_GLOBAL);
    if (!libraryHandle) {
        std::cerr << "Error loading shared library: " << dlerror() << std::endl;
        return 1;
    }

    // Get the address of the function named "foo" from the library
    FooFunction fooFunc = reinterpret_cast<FooFunction>(dlsym(libraryHandle, "foo"));
    if (!fooFunc) {
        std::cerr << "Error getting symbol 'foo': " << dlerror() << std::endl;
        dlclose(libraryHandle); // Clean up
        return 1;
    }

    // Call the function
    fooFunc();

    // Clean up
    dlclose(libraryHandle);

    return 0;
}
