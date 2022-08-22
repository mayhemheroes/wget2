
struct wget_hsts_db_vtable;

// HSTS database base type
typedef struct {
	struct wget_hsts_db_vtable *vtable;
} wget_hsts_db_t;

// vtable for implementation
struct wget_hsts_db_vtable {
	int (*load)(wget_hsts_db_t *);
	int (*save)(wget_hsts_db_t *);	
	int (*host_match)(wget_hsts_db_t *, const char *, uint16_t);
	void (*add)(wget_hsts_db_t *, const char *, uint16_t, time_t, int);
	void (*free)(wget_hsts_db_t *);
};

/**
 * Custom HSTS databases can be implemented as the following:
 *     typedef struct {
 *         wget_hsts_db_t parent;
 *         derrived class members...
 *     } my_hsts_db_t;
 *
 *     static int impl_load(wget_hsts_db_t *parent_hsts_db)
 *     {
 *         my_hsts_db_t *hsts_db = (my_hsts_db_t *) parent_hsts_db;
 *
 *         implemetation...
 *     }
 *
 *     static int impl_save(wget_hsts_db_t *parent_hsts_db)
 *     {
 *         my_hsts_db_t *hsts_db = (my_hsts_db_t *) parent_hsts_db;
 *
 *         implementation...
 *     }
 *
 *     static int impl_host_match(wget_hsts_db_t *parent_hsts_db,
 *         const char *host, uint16_t port)
 *     {
 *         my_hsts_db_t *hsts_db = (my_hsts_db_t *) parent_hsts_db;
 *
 *         implementation...
 *     }
 *
 *     static void impl_add(wget_hsts_db_t *parent_hsts_db, 
 *         const char *hostname, uint16_t port, time_t maxage, int include_subdomains)
 *     {
 *         my_hsts_db_t *hsts_db = (my_hsts_db_t *) parent_hsts_db;
 *
 *         implementation...
 *     }
 *
 *     static int impl_free(wget_hsts_db_t *parent_hsts_db)
 *     {
 *         my_hsts_db_t *hsts_db = (my_hsts_db_t *) parent_hsts_db;
 *
 *         free all members...
 *
 *         wget_free(hsts_db);
 *     }
 *
 *
 *     struct my_hsts_db_vtable = {
 *         .save = impl_save;
 *         .load = impl_load;
 *         .host_match = impl_host_match;
 *         .add = impl_add;
 *         .free = impl_free;
 *     }
 *
 *     wget_hsts_db_t *my_hsts_db_create(...)
 *     {
 *         my_hsts_db_t *hsts_db = wget_malloc(sizeof(my_hsts_db_t));
 *
 *         hsts_db->parent.vtable = my_hsts_db_vtable;
 *
 *         derrived class initialization...
 *
 *         return (wget_hsts_db_t *) hsts_db;
 *     }
 */

// Functions with changed prototypes

int wget_hsts_db_load(wget_hsts_db_t *hsts_db);
//< No fname parameter

int wget_hsts_db_save(wget_hsts_db_t *hsts_db);
//< No fname parameter

wget_hsts_db_t *wget_hsts_db_init(wget_hsts_db_t *hsts_db, const char *fname);
//< New paramater fname

void wget_hsts_db_add(wget_hsts_db_t *hsts_db, const char *hostname, uint16_t port, time_t maxage, int include_subdomains);
//< expanded wget_hsts_t inline

