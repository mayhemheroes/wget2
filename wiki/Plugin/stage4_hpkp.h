
struct wget_hpkp_db_vtable;

// HPKP database base type
typedef struct {
	struct wget_hpkp_db_vtable *vtable;
} wget_hpkp_db_t;

// vtable for implementation
struct wget_hpkp_db_vtable {
	int (*load)(wget_hpkp_db_t *);
	int (*save)(wget_hpkp_db_t *);	
	void (*free)(wget_hpkp_db_t *);
	void (*add)(wget_hpkp_db_t *, wget_hpkp_t *hpkp);
	bool (*check_pubkey)(wget_hpkp_db_t *, const char *, const void *, size_t);
};

/**
 * Custom HPKP databases can be implemented as the following:
 *     typedef struct {
 *         wget_hpkp_db_t parent;
 *         derrived class members...
 *     } my_hpkp_db_t;
 *
 *     static int impl_load(wget_hpkp_db_t *parent_hpkp_db)
 *     {
 *         my_hpkp_db_t *hpkp_db = (my_hpkp_db_t *) parent_hpkp_db;
 *
 *         implemetation...
 *     }
 *
 *     static int impl_save(wget_hpkp_db_t *parent_hpkp_db)
 *     {
 *         my_hpkp_db_t *hpkp_db = (my_hpkp_db_t *) parent_hpkp_db;
 *
 *         implementation...
 *     }
 *
 *     static bool impl_check_pubkey(wget_hpkp_db_t *parent_hpkp_db,
 *         const char *host, const void *pubkey, size_t pubkey_size)
 *     {
 *         my_hpkp_db_t *hpkp_db = (my_hpkp_db_t *) parent_hpkp_db;
 *
 *         implementation...
 *     }
 *
 *     static void impl_add(wget_hpkp_db_t *parent_hpkp_db, wget_hpkp_t *hpkp)
 *     {
 *         my_hpkp_db_t *hpkp_db = (my_hpkp_db_t *) parent_hpkp_db;
 *
 *         implementation...
 *     }
 *
 *     static int impl_free(wget_hpkp_db_t *parent_hpkp_db)
 *     {
 *         my_hpkp_db_t *hpkp_db = (my_hpkp_db_t *) parent_hpkp_db;
 *
 *         free all members...
 *
 *         wget_free(hpkp_db);
 *     }
 *
 *
 *     struct my_hpkp_db_vtable = {
 *         .save = impl_save;
 *         .load = impl_load;
 *         .check_pubkey = impl_check_pubkey;
 *         .add = impl_add;
 *         .free = impl_free;
 *     }
 *
 *     wget_hpkp_db_t *my_hpkp_db_create(...)
 *     {
 *         my_hpkp_db_t *hpkp_db = wget_malloc(sizeof(my_hpkp_db_t));
 *
 *         hpkp_db->parent.vtable = my_hpkp_db_vtable;
 *
 *         derrived class initialization...
 *
 *         return (wget_hpkp_db_t *) hpkp_db;
 *     }
 */

// Functions with changed prototypes

int wget_hpkp_db_load(wget_hpkp_db_t *hpkp_db);
//< No fname parameter

int wget_hpkp_db_save(wget_hpkp_db_t *hpkp_db);
//< No fname parameter

wget_hpkp_db_t *wget_hpkp_db_init(wget_hpkp_db_t *hpkp_db, const char *fname);
//< New paramater fname


