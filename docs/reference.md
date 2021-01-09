# Reference
## Functions
- **[``ospl_create_library``](/{{ site.baseurl }}/reference/ospl_create_library)**  
	create an ospl library.
- **[``ospl_import_photo``](/{{ site.baseurl }}/reference/ospl_import_photo)**  
	import a photo into library
- **[``ospl_import_photo_in_album``](/{{ site.baseurl }}/reference/ospl_import_photo_in_album)**  
	import a photo directly into an existing album
- **[``ospl_import_folder``](/{{ site.baseurl }}/reference/ospl_import_folder)**  
	import a folder full of photos
- **[``ospl_import_folder_in_album``](/{{ site.baseurl }}/reference/ospl_import_folder_in_album)**  
	import a folder full of photos directly into an existing album
- **[``ospl_album_list``](/{{ site.baseurl }}/reference/ospl_album_list)**  
	get the entire album list stored in a library
- **[``ospl_album_list_photos``](/{{ site.baseurl }}/reference/ospl_album_list_photos)**  
	get the photo list from an album
- **[``ospl_photo_associated_album``](/{{ site.baseurl }}/reference/ospl_photo_associated_album)**  
	get the albums where a specific photo is stored
- **[``ospl_album_create``](/{{ site.baseurl }}/reference/ospl_album_create)**  
	create an album in an ospl library
- **[``ospl_album_rename``](/{{ site.baseurl }}/reference/ospl_album_rename)**  
	rename an album from an ospl library
- **[``ospl_album_delete``]()**  
	delete an album from an ospl library
- **[``ospl_album_add_photo``]()**  
	add a photo to an existing album
- **[``ospl_album_delete_photo``]()**  
	delete a photo from an album
- **[``ospl_album_move_photo``]()**  
	move a photo from an album to another album
- **[``ospl_photo_get``]()**  
	get informations about a specific photo
- **[``ospl_photo_list``]()**  
	list every photo from a library
- **[``ospl_photo_delete``]()**  
	delete a specific photo from a library

## Data structures

### stockage.h

```c
typedef struct			s_photos
{
	int					id;
	char				hash[33];
	char				original_name[255];
	char				new_name[255];
	char				import_datetime[32];
	char				random[11];
	uint16_t			import_year;
	uint8_t				import_month;
	uint8_t				import_day;
	uint8_t				import_hour;
	uint8_t				import_minute;
	uint8_t				import_second;
	uint32_t			exif_height;
	uint32_t			exif_width;
	char				exif_brand[32];
	char				exif_peripheral[32];
	uint8_t				fav;
}						t_photos;
```
The ``t_photos`` data structure  is used to get information about a photo or adding a photo to the database.

```c
typedef struct			s_album
{
	int					id;
	char				name[255];
}						t_album;
```
the ``t_album`` data structure is used to get information about an album or adding an album to the database.

```c
typedef struct			s_db
{
	sqlite3				*db;
	char				*path;
	uint8_t				transaction;
	uint8_t				commit;
}						t_db;
```
The ``t_db`` data structure is used to communicate with the database.

## Folder structure
When you create an ospl library (calling **[``ospl_create_library``](/{{ site.baseurl }}/reference/ospl_create_library)** function) the following files and folders are created:

| ``path``                          | ``description``                                              | ``introduced in version`` |
| --------------------------------- | ------------------------------------------------------------ | ---------------------- |
| ``library_name/``                 | the folder of the entire library with its name           | ``0.1.0``              |
| ``library_name/database.db``      | the database containing all infos about the photos [database structure](#database) | ``0.1.0``              |
| ``library_name/photos/``        | the folder where every album is created and stored       | ``0.1.0``              |
| ``library_name/photos/import/`` | the default folder where photos are imported           | ``0.1.0``              |
| ``library_name/thumbnails``       | the location of the thumbnails of every photo          | ``0.1.0``              |

## Database

To understand better, here is a updated database diagram (captured from [here](https://dbdiagram.io/d/5ec97ad039d18f5553ffa8cf)):

![database_diagram.png](https://raw.githubusercontent.com/AngeloFrangione/libospl/master/database_diagram.png)

In this section every table and column is explained, and an example is provided to better understand the database structure.

### Main tables

#### photos (introduced in version ``0.1.0``)

| ``column name``     | ``description``                                              | ``example``                                | ``introduced in version`` |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------ | ---------------------- |
| ``id``              | unique identifier of the photo                             | ``1``                                      | ``0.1.0``              |
| ``hash``            | hash of the photo created at import time                   | ``"99e94717dcd8f9538482372d3254c1"``       | ``0.1.0``              |
| ``original_name``   | original name of the photo when imported                   | ``"IMG_1001.jpg"``                         | ``0.1.0``              |
| ``new_name``        | new name composed of ``original_name`` ``import_datetime`` column | ``"2021-01-04-23-47-26-230_IMG_1001.jpg"`` | ``0.1.0``              |
| ``import_datetime`` | import date and time                                         | ``"2021-01-04-23-47-26-230"``              | ``0.1.0``              |
| ``import_year``     | import year                                                  | ``2021``                                   | ``0.1.0``              |
| ``import_month``    | import month                                                 | ``1``                                      | ``0.1.0``              |
| ``import_day``      | import day                                                   | ``04``                                     | ``0.1.0``              |
| ``import_hour``     | import hour                                                  | ``23``                                     | ``0.1.0``              |
| ``import_minute``    | import minute                                                | ``50``                                     | ``0.1.0``              |
| ``import_second``   | import second                                                | ``30``                                     | ``0.1.0``              |
| ``exif_time``       | time when the photo was taken (optional)                   | ``0``                                      | ``0.1.0``              |
| ``exif_height``     | height of the image (optional)                               | ``1080``                                   | ``0.1.0``              |
| ``exif_width``      | width of the image (optional)                                | ``1920``                                   | ``0.1.0``              |
| ``exif_brand``      | brand of the camera that has taken the photo               | ``"Canon"``                                | ``0.1.0``              |
| ``exif_model``      | model of the camera that has taken the photo               | ``"EOS 5D"``                               | ``0.1.0``              |
| ``fav``             | indicate if the photo is marked as a favorite             | ``1``                                      | ``0.1.0``              |
| ``random``          | random generated 10 digits number at import time             | ``0905043953``                             | ``0.1.0``              |

#### albums (introduced in version ``0.1.0``)

| ``column name`` | ``description``                | ``example``      | ``introduced in version`` |
| --------------- | ------------------------------ | ---------------- | ---------------------- |
| ``id``          | unique identifier of the album | ``1``            | ``0.1.0``              |
| ``name``        | name of the album              | ``"Italy 2015"`` | ``0.1.0``              |

#### folders (introduced in version ``0.1.0``)

| ``column name`` | ``description``                 | ``example``    | ``introduced in version`` |
| --------------- | ------------------------------- | -------------- | ---------------------- |
| ``id``          | unique identifier of the folder | ``1``          | ``0.1.0``              |
| ``name``        | name of the folder              | ``"Holidays"`` | ``0.1.0``              |

#### settings (introduced in version ``0.1.0``)

| ``column name`` | ``description``      | ``example``   | ``introduced in version`` |
| --------------- | -------------------- | ------------- | ---------------------- |
| ``name``        | name of the setting  | ``"version"`` | ``0.1.0``              |
| ``value``       | value of the setting | ``"0.1.0"``   | ``0.1.0``              |

### Link tables

#### contains  (album contains photos) (introduced in version ``0.1.0``)

| ``column name``       | ``description``                               | ``example`` | ``introduced in version`` |
| --------------------- | --------------------------------------------- | ----------- | ---------------------- |
| ``containing_album``  | ``id`` of the album that contains the photo | ``1``       | ``0.1.0``              |
| ``contained_photo`` | ``ìd`` of the photo contained in the album  | ``24``      | ``0.1.0``              |

#### holds (folder holds albums ) (introduced in version ``0.1.0``)

| ``column name``    | ``description``                           | ``example`` | ``introduced in version`` |
| ------------------ | ----------------------------------------- | ----------- | ---------------------- |
| ``held_album`` | ``id`` of the album held by the folder | ``2``       | ``0.1.0``              |
| ``held_folder`` | ``id`` of the folder that holds the album | ``3``       | ``0.1.0``              |

#### includes  (folder holds folder) (introduced in version ``0.1.0``)

| ``column name``      | ``description``                                   | ``example`` | ``introduced in version`` |
| -------------------- | ------------------------------------------------- | ----------- | ---------------------- |
| ``including_folder`` | ``id`` of the folder that includes another folder | ``2``       | ``0.1.0``              |
| ``included_folder``  | ``id`` of the folder included by the other folder | ``3``       | ``0.1.0``              |
