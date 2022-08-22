
struct wget_ocsp_db_vtable;

// OCSP database base type
typedef struct {
	struct wget_ocsp_db_vtable *vtable;
} wget_ocsp_db_t;

// vtable for implementation
struct wget_ocsp_db_vtable {
	int (*load)(wget_ocsp_db_t *);
	int (*save)(wget_ocsp_db_t *);	
	int (*fingerprint_in_cache)(const wget_ocsp_db_t *, const char *, int *);
	int (*hostname_is_valid)(const wget_ocsp_db_t *, const char *);
	void (*add_fingerprint)(wget_ocsp_db_t *, const char *, time_t, int);
	void (*add_host)(wget_ocsp_db_t *, const char *, time_t);
	void (*free)(wget_ocsp_db_t *);
};

/**
 * Custom OCSP databases can be implemented as the following:
 *     typedef struct {
 *         wget_ocsp_db_t parent;
 *         derrived class members...
 *     } my_ocsp_db_t;
 *
 *     static int impl_load(wget_ocsp_db_t *parent_ocsp_db)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implemetation...
 *     }
 *
 *     static int impl_save(wget_ocsp_db_t *parent_ocsp_db)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implementation...
 *     }
 *
 *     static int impl_fingerprint_in_cache(const wget_ocsp_db_t *parent_ocsp_db, const char *fingerprint, int *valid)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implementation...
 *     }
 * 
 *     static int impl_hostname_is_valid(const wget_ocsp_db_t *parent_ocsp_db, const char *hostname)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implementation...
 *     }
 *
 *     static void impl_add_fingerprint(wget_ocsp_db_t *parent_ocsp_db, const char *fingerprint, time_t maxage, int valid)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implementation...
 *     }
 *
 *     static void impl_add_host(wget_ocsp_db_t *parent_ocsp_db, const char *fingerprint, time_t maxage)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         implementation...
 *     }
 *
 *     static int impl_free(wget_ocsp_db_t *parent_ocsp_db)
 *     {
 *         my_ocsp_db_t *ocsp_db = (my_ocsp_db_t *) parent_ocsp_db;
 *
 *         free all members...
 *
 *         wget_free(ocsp_db);
 *     }
 *
 *
 *     struct my_ocsp_db_vtable = {
 *         .save = impl_save;
 *         .load = impl_load;
 *         .fingerprint_in_cache = impl_fingerprint_in_cache;
 *         .hostname_is_valid = impl_hostname_is_valid;
 *         .add_fingerprint = impl_add_fingerprint;
 *         .add_host = impl_add_host;
 *         .add = impl_add;
 *         .free = impl_free;
 *     }
 *
 *     wget_ocsp_db_t *my_ocsp_db_create(...)
 *     {
 *         my_ocsp_db_t *ocsp_db = wget_malloc(sizeof(my_ocsp_db_t));
 *
 *         ocsp_db->parent.vtable = my_ocsp_db_vtable;
 *
 *         derrived class initialization...
 *
 *         return (wget_ocsp_db_t *) ocsp_db;
 *     }
 */

// Functions with changed prototypes

int wget_ocsp_db_load(wget_ocsp_db_t *ocsp_db);
//< No fname parameter

int wget_ocsp_db_save(wget_ocsp_db_t *ocsp_db);
//< No fname parameter

wget_ocsp_db_t *wget_ocsp_db_init(wget_ocsp_db_t *ocsp_db, const char *fname);
//< New paramater fname

void wget_ocsp_db_add_fingerprint(wget_ocsp_db_t *ocsp_db, const char *fingerprint, time_t maxage, int valid);
//< Expanded wget_ocsp_t inline

void wget_ocsp_db_add_host(wget_ocsp_db_t *ocsp_db, const char *hostname, time_t maxage);
//< Expanded wget_ocsp_t inline

