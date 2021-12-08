#define INF 99999
#define MAX_CITIES 21

char *knownCitiesList;
char *getName(int c);

struct Edge;
struct Graph;

struct Graph* createGraph(int E);
void addEdge(struct Graph* graph, int src, int dest, int wgt, int i);
void BellmanFord(struct Graph* graph, int source, int destination);
