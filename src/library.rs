pub struct OsplLibrary {
    storage_path: String,
    library_path: String,
}

pub fn ospl_library_new(storage_path: String, library_path: String) -> OsplLibrary {
    let library = OsplLibrary {
        storage_path: storage_path,
        library_path: library_path,
    };

    library
}
