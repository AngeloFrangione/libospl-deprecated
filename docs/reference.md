# Reference
## Functions
- **[ospl_create_library](/{{ site.baseurl }}/reference/ospl_create_library)**  
	create a ospl library.
- **[ospl_import_picture](/{{ site.baseurl }}/reference/ospl_import_picture)**  
	import a picture into library
- **[ospl_import_picture_in_album]()**  
	import a picture directly into an existing album
- **[ospl_import_folder]()**  
	import a folder full of pictures
- **[ospl_import_folder_in_album]()**  
	import a folder full of pictures directly into an existing album
- **[ospl_list_albums]()**  
	get the entire album list stored in a library
- **[ospl_album_listpic]()**  
	get the picture list from an album
- **[ospl_album_assocpic]()**  
	get the albums were a specific picture is stored
- **[ospl_create_album]()**  
	create an album in a ospl library
- **[ospl_rename_album]()**  
	rename an album from an ospl library
- **[ospl_delete_album]()**  
	delete an album from an ospl library
- **[ospl_album_addpic]()**  
	add a picture to an existing album
- **[ospl_album_delpic]()**  
	delete a picture from an album
- **[ospl_album_movepic]()**  
	move a picture from an album to another album
- **[ospl_picture_get]()**  
	get informations about a specific picture
- **[ospl_picture_list]()**  
	list every picture from a library
- **[ospl_picture_delete]()**  
	delete a specific picture from a library

## Structure
When you create an ospl library (calling **[ospl_create_library](/{{ site.baseurl }}/reference/ospl_create_library)** function) the following files and folders are created:

| ``path``                          | ``description``                                              | ``introduced in version`` |
| --------------------------------- | ------------------------------------------------------------ | ---------------------- |
| ``library_name/``                 | ``the folder of the entire library with its name``           | ``0.1.0``              |
| ``library_name/database.db``      | ``the database containing all infos about the pictures`` [database structure](#database) | ``0.1.0``              |
| ``library_name/pictures/``        | ``the folder where every album is created and stored``       | ``0.1.0``              |
| ``library_name/pictures/import/`` | ``the default folder where pictures are imported``           | ``0.1.0``              |
| ``library_name/thumbnails``       | ``the location of the thumbnails of every picture``          | ``0.1.0``              |

## Database

for easier understanding here is a updated database diagram (captured from [here](https://dbdiagram.io/d/5ec97ad039d18f5553ffa8cf)):

![database_diagram.png](https://raw.githubusercontent.com/AngeloFrangione/libospl/master/database_diagram.png)

In this section every table and column is explained, and an example is provided for best understanding of the database structure.

### Main tables

#### photos (introduced in version ``0.1.0``)

| ``column name``     | ``description``                                              | ``example``                                | ``introduced in version`` |
| ------------------- | ------------------------------------------------------------ | ------------------------------------------ | ---------------------- |
| ``id``              | unique identifier of the picture                             | ``1``                                      | ``0.1.0``              |
| ``hash``            | hash of the picture created at import time                   | ``"99e94717dcd8f9538482372d3254c1"``       | ``0.1.0``              |
| ``original_name``   | original name of the picture when imported                   | ``"IMG_1001.jpg"``                         | ``0.1.0``              |
| ``new_name``        | new name composed of ``original_name`` ``import_datetime`` column | ``"2021-01-04-23-47-26-230_IMG_1001.jpg"`` | ``0.1.0``              |
| ``import_datetime`` | import date and time                                         | ``"2021-01-04-23-47-26-230"``              | ``0.1.0``              |
| ``import_year``     | import year                                                  | ``2021``                                   | ``0.1.0``              |
| ``import_month``    | import month                                                 | ``1``                                      | ``0.1.0``              |
| ``import_day``      | import day                                                   | ``04``                                     | ``0.1.0``              |
| ``import_hour``     | import hour                                                  | ``23``                                     | ``0.1.0``              |
| ``import_minut``    | import minute                                                | ``50``                                     | ``0.1.0``              |
| ``import_second``   | import second                                                | ``30``                                     | ``0.1.0``              |
| ``exif_time``       | time when the picture was taken (optional)                   | ``0``                                      | ``0.1.0``              |
| ``exif_height``     | height of the image (optional)                               | ``1080``                                   | ``0.1.0``              |
| ``exif_width``      | width of the image (optional)                                | ``1920``                                   | ``0.1.0``              |
| ``exif_brand``      | brand of the camera that has taken the picture               | ``"Canon"``                                | ``0.1.0``              |
| ``exif_model``      | model of the camera that has taken the picture               | ``"EOS 5D"``                               | ``0.1.0``              |
| ``fav``             | indicate if the picture is market as a favorite              | ``1``                                      | ``0.1.0``              |
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

#### contains  (album contains pictures) (introduced in version ``0.1.0``)

| ``column name``       | ``description``                               | ``example`` | ``introduced in version`` |
| --------------------- | --------------------------------------------- | ----------- | ---------------------- |
| ``containing_album``  | ``id`` of the album that contains the picture | ``1``       | ``0.1.0``              |
| ``contained_picture`` | ``ìd`` of the picture contained in the album  | ``24``      | ``0.1.0``              |

#### holds (folder holds albums ) (introduced in version ``0.1.0``)

| ``column name``    | ``description``                           | ``example`` | ``introduced in version`` |
| ------------------ | ----------------------------------------- | ----------- | ---------------------- |
| ``holded_album``   | ``id`` of the album holded by the folder  | ``2``       | ``0.1.0``              |
| ``holding_folder`` | ``id`` of the folder that holds the album | ``3``       | ``0.1.0``              |

#### includes  (folder holds folder) (introduced in version ``0.1.0``)

| ``column name``      | ``description``                                   | ``example`` | ``introduced in version`` |
| -------------------- | ------------------------------------------------- | ----------- | ---------------------- |
| ``including_folder`` | ``id`` of the folder that includes another folder | ``2``       | ``0.1.0``              |
| ``included_folder``  | ``id`` of the folder included by the other folded | ``3``       | ``0.1.0``              |
