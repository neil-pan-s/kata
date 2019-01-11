function dedup(array) {
    //return Array.from(new Set(array));
    return [...new Set(array)];
}

dedup([1, 1, 2, 3]) // [1, 2, 3]