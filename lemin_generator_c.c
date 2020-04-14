#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

const char *generate_name_upper = "ABCDEFGHIJKMNOPQRSTUVWXYZ";
const char *generate_name_lower = "abcdefghijklmnopqrstuvwxyz___";

typedef struct s_room {
	int field_0;
	int field_4;
	char *name;
	int field_10;
	int field_14;
	ssize_t field_18;
	int field_20;
	int field_24;
	struct s_room *field_28;
	ssize_t field_30;
	struct s_room *field_38;
	struct s_tube *tubes;
	struct s_room *next;
	struct s_room *prev;
} t_room;

typedef struct s_link {
	struct s_room *src;
	struct s_room *dst;
	struct s_link *next;
} t_link;

typedef struct s_header {
	struct s_room *start;
	struct s_room *end;
	struct s_room *tube_head;
	struct s_room *tube_tail;
} t_header;

typedef struct s_tube {
	struct s_room *room;
	struct s_tube *next;
} t_tube;

typedef struct s_maze {
	int algo_ret;
	int start_ants;
	int field_8; // other ants
	int field_C;
	int field_10;
	int total_nodes;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
	ssize_t field_28;
	ssize_t field_30;
	struct s_link *links;
	struct s_header *header;
	int gen_type;
} t_maze;

void
ft_usage(void)
{
	fputs("\nusage: ./generator [option]\noptions:\n\t--help : to read the manual\n\n", stderr);
	exit(0);
}

void
man(void)
{
	fprintf(stderr, "\noptions:\n"
			"\t--help : to read the manual\n"
			"\t--flow-one : generates an ant farm with distinctive path and [1] ant in it\n"
			"\t--flow-ten : generates an ant farm with distinctive path and approximately [10] ants in it\n"
			"\t--flow-thousand : generates an ant farm with distinctive path and approximately [100] ants in it\n"
			"\t--big : generates a big map (approximately [1000] rooms) to test the time complexity\n"
			"\t--big-superposition : generates a big map with overlapping paths\n\n");
	exit(0);
}

int
flag(const char *arg)
{
	if (!strcmp(arg, "--help"))
		man();
	if (!strcmp(arg, "--flow-one"))
		return 0;
	if (!strcmp(arg, "--flow-ten"))
		return 1;
	if (!strcmp(arg, "--flow-thousand"))
		return 2;
	if (!strcmp(arg, "--big"))
		return 3;
	if (strcmp(arg, "--big-superposition"))
		ft_usage();
	return 4;
}

int
lem_options(int argc, const char **argv)
{
	if (argc != 2)
		ft_usage();
	return flag(argv[1]);
}

void
ft_error(void)
{
	perror("Fatal error");
	exit(1);
}

void
create_header(struct s_maze *maze)
{
	maze->header = calloc(1, sizeof(struct s_header));
	if (!maze->header)
		ft_error();
}

int
room_exists(struct s_maze *maze, const char *name)
{
	struct s_room *v3;

	v3 = maze->header->tube_tail;
	if (maze->header->start->name && !strcmp(maze->header->start->name, name))
		return 1;
	if (maze->header->end->name && !strcmp(maze->header->end->name, name))
		return 1;
	while (v3) {
		if (!strcmp(v3->name, name))
			return 1;
		v3 = v3->next;
	}
	return 0;
}

void
add_room(struct s_maze *maze, struct s_room *room)
{
	if (room->name == maze->header->start->name)
		room->field_18 = 1LL;
	room->next = maze->header->tube_tail;
	if (maze->header->tube_tail)
		maze->header->tube_tail->prev = room;
	maze->header->tube_tail = room;
	++maze->total_nodes;
	if (!maze->header->tube_head)
		maze->header->tube_head = room;
}

void
skip_end(struct s_tube *a1, struct s_room *a2)
{
	a1->next = a2->tubes->next;
	a2->tubes->next = a1;
}

void
save_link(struct s_maze *maze, struct s_room *src, struct s_room *dst)
{
	struct s_link *v3;

	v3 = calloc(1, sizeof(*v3));
	if (!v3)
		ft_error();
	v3->src = src;
	v3->dst = dst;
	v3->next = maze->links;
	maze->links = v3;
}

void
create_tube(struct s_maze *maze, struct s_room *src, struct s_room *dst)
{
	struct s_tube *v3;
	struct s_tube *v4;

	v3 = calloc(1, sizeof(*v3));
	if (!v3)
		ft_error();
	v4 = calloc(1, sizeof(*v4));
	if (!v4)
		ft_error();
	v4->room = dst;
	v3->room = src;
	if (src->tubes && src->tubes->room == maze->header->end) {
		skip_end(v4, src);
	} else {
		v4->next = src->tubes;
		src->tubes = v4;
	}
	if (dst->tubes && dst->tubes->room == maze->header->end) {
		skip_end(v3, dst);
	} else {
		v3->next = dst->tubes;
		dst->tubes = v3;
	}
	save_link(maze, src, dst);
}

struct s_room*
create_room(struct s_maze *maze, char *name) {
	struct s_room *new;

	new = calloc(1, sizeof(*new));
	if (!new)
		ft_error();
	new->name = name;
	add_room(maze, new);
	return new;
}

char*
generate_name(struct s_maze *maze)
{
	char *ret;

	ret = calloc(5, sizeof(*ret));
	if (!ret)
		ft_error();
	ret[0] = generate_name_upper[rand() % 0x19];
	ret[1] = generate_name_lower[rand() % 0x1D];
	ret[2] = generate_name_lower[rand() % 0x1D];
	ret[3] = rand() % 10 + 48;
	if (!room_exists(maze, ret))
		return ret;
	free(ret);
	return generate_name(maze);
}

t_room*
generate_path(t_maze *maze, t_room *start, t_room *end, int length)
{
	int v4;
	char *new_name;
	t_room *new_room;
	t_room *cur;
	int v8;

	v8 = length;
	for (cur = start; ; cur = new_room) {
		v4 = v8--;
		if (!v4)
			break;
		new_name = generate_name(maze);
		new_room = create_room(maze, new_name);
		create_tube(maze, cur, new_room);
	}
	create_tube(maze, cur, end);
	return cur;
}

t_room*
random_room(t_maze *maze)
{
	int v1;
	t_room *i;
	int v4;

	v4 = rand() % maze->total_nodes;
	for (i = maze->header->tube_tail; ; i = i->next) {
		v1 = v4--;
		if (!v1)
			break;
	}
	return i;
}

void
generate_one(t_maze *maze, t_room *start, t_room *end)
{
	int v3, v4, v5, v6;
	t_room *rnd_room, *new_room;
	int v9, v10;

	maze->start_ants = 1;
	maze->field_8 = maze->start_ants;
	v10 = rand() % 5 + 1;
	v3 = rand();
	generate_path(maze, start, end, v3 % 10 + 26);
	while (1) {
		v4 = v10--;
		if (!v4)
			break;
		v5 = rand();
		generate_path(maze, start, end, v5 % 45 + 55);
	}
	v9 = rand() % 100;
	while (1) {
		v6 = v9--;
		if (!v6)
			break;
		new_room = calloc(1, sizeof(*new_room));
		if (!new_room)
			ft_error();
		new_room->name = generate_name(maze);
		rnd_room = random_room(maze);
		create_tube(maze, rnd_room, new_room);
		add_room(maze, new_room);
	}
}

void
generate_ten(t_maze *maze, t_room *start, t_room *end)
{
	int v3, v4, v5, v6, v7;
	t_room *v8, *v9;
	int v10, v11, v12;

	maze->start_ants = rand() % 8 + 9;
	maze->field_8 = maze->start_ants;
	v11 = maze->start_ants / 3 + rand() % (maze->start_ants - maze->start_ants / 3);
	while (1) {
		v3 = v11--;
		if (!v3)
			break;
		v4 = rand();
		generate_path(maze, start, end, v4 % 10 + 26);
	}
	v12 = rand() % 5 + 1;
	while (1) {
		v5 = v12--;
		if (!v5)
			break;
		v6 = rand();
		generate_path(maze, start, end, v6 % 45 + 55);
	}
	v10 = rand() % 100;
	while (1) {
		v7 = v10--;
		if (!v7)
			break;
		v9 = calloc(1, sizeof(*v9));
		v9->name = generate_name(maze);
		v8 = random_room(maze);
		create_tube(maze, v8, v9);
		add_room(maze, v9);
	}
}

void
generate_thousand(t_maze *maze, t_room *start, t_room *end)
{
	int v3, v4, v5, v6, v7;
	t_room *v8, *v9;
	int v10, v11, v12;

	maze->start_ants = rand() % 75 + 85;
	maze->field_8 = maze->start_ants;
	v11 = rand() % 5 + 9;
	while (1) {
		v3 = v11--;
		if (!v3)
			break;
		v4 = rand();
		generate_path(maze, start, end, v4 % 10 + 15);
	}
	v12 = rand() % 4 + 2;
	while (1) {
		v5 = v12--;
		if (!v5)
			break;
		v6 = rand();
		generate_path(maze, start, end, v6 % 20 + 35);
	}
	v10 = rand() % 180;
	while (1) {
		v7 = v10--;
		if (!v7)
			break;
		v9 = calloc(1, sizeof(*v9));
		if (!v9)
			break;
		v9->name = generate_name(maze);
		v8 = random_room(maze);
		create_tube(maze, v8, v9);
		add_room(maze, v9);
	}
}

void
generate_useless(t_maze *maze, t_room *current_room, t_room *new_room, int length, int a5)
{
	int v5;
	char *new_name;
	t_room *a3, *a2;
	int len;
	t_room *v11;

	v11 = new_room;
	len = length;
	a2 = current_room;
	while (1) {
		v5 = len--;
		if (!v5 )
			break;
		new_name = generate_name(maze);
		a3 = create_room(maze, new_name);
		a3->field_0 = a5;
		create_tube(maze, a2, a3);
		a2 = a3;
		++maze->field_18;
	}
	create_tube(maze, a2, v11);
}

void
generate_path_with_useless(t_maze *maze, t_room *start, t_room *end, int length)
{
	int v4;
	char *new_name;
	int v6, v7, v8;
	t_room *new_room;
	int v10;
	t_room *cur;
	int len;

	len = length;
	v10 = 0;
	for (cur = start; ; cur = new_room) {
		v4 = len--;
		if (!v4)
			break;
		new_name = generate_name(maze);
		new_room = create_room(maze, new_name);
		v6 = rand();
		v7 = v10++;
		generate_useless(maze, cur, new_room, v6 % 4 + 2, v7);
		new_room->field_0 = v10;
		++maze->field_18;
		create_tube(maze, cur, new_room);
	}
	v8 = rand() % 4 + 2;
	generate_useless(maze, cur, end, v8, v10);
	create_tube(maze, cur, end);
}

void
generate_star(t_maze *maze, t_room *start, t_room *end, int length)
{
	unsigned int v4;
	char *v5;
	unsigned int v6;
	char *v7;
	unsigned int v8, v8a;
	t_room *v8_4, *v8_4a, *a2, *a2a;
	unsigned int v14;
	t_room *v15;

	v15 = end;
	v14 = length;
	a2 = start;
	v8 = length;
	while (1) {
		v4 = v8--;
		if (!v4)
			break;
		v5 = generate_name(maze);
		v8_4 = create_room(maze, v5);
		create_tube(maze, a2, v8_4);
		a2 = v8_4;
	}
	a2a = v15;
	v8a = v14;
	while (1) {
		v6 = v8a--;
		if (!v6)
			break;
		v7 = generate_name(maze);
		v8_4a = create_room(maze, v7);
		create_tube(maze, a2a, v8_4a);
		a2a = v8_4a;
	}
}

int
tube_already_exist(t_room *src, t_room *dst)
{
	t_tube *i;

	for (i = src->tubes; i; i = i->next) {
		if (i->room == dst)
			return 1;
	}
	return 0;
}

void
entangle(t_maze *maze)
{
	int v1, v2;
	bool v3;
	char v4;
	t_room *a3, *a2;
	int v7, v8;

	v7 = rand() % (6 * maze->field_18);
	a2 = maze->header->tube_tail;
	while (1) {
		v1 = v7--;
		if (!v1)
			break;
		a2 = a2->next;
		while (1) {
			v4 = 1;
			if (a2)
				v4 = ~(a2->field_0 != 0);
			if (!(v4 & 1))
				break;
			if (a2)
				a2 = a2->next;
			else
				a2 = maze->header->tube_tail;
		}
	}
	a3 = maze->header->tube_tail;
	v8 = rand() % (6 * maze->field_18);
	while (1) {
		v2 = v8--;
		if (!v2)
			break;
		a3 = a3->next;
		while (1) {
			v3 = 1;
			if (a3)
				v3 = a3->field_0 != a2->field_0;
			if (!v3)
				break;
			if (a3)
				a3 = a3->next;
			else
				a3 = maze->header->tube_tail;
		}
	}
	if (a2 != a3 && !tube_already_exist(a2, a3))
		create_tube(maze, a2, a3);
}

void
generate_big(t_maze *maze, t_room *start, t_room *end)
{
	int v3, v4, v5, v6, v7, v8;
	t_room *v9;
	int v10, v11, v12;
	t_room *a2;
	int v14, v15, v16, v17;

	maze->start_ants = rand() % 275 + 185;
	maze->field_8 = maze->start_ants;
	v16 = rand() % 8 + 7;
	while (1) {
		v3 = v16--;
		if (!v3)
			break;
		v12 = rand() % 18;
		v11 = rand() % 18 + v12;
		v4 = rand();
		generate_path_with_useless(maze, start, end, v4 % 8 + v11 + 10);
	}
	v17 = rand() % 8 + 1;
	while (1) {
		v5 = v17--;
		if (!v5)
			break;
		v10 = rand() % 25;
		v6 = rand();
		generate_star(maze, start, end, v6 % 25 + v10 + 8);
	}
	v15 = rand() % 250 + 250;
	while (1) {
		v7 = v15--;
		if (!v7)
			break;
		entangle(maze);
	}
	v14 = rand() % 600 + 400;
	while (1) {
		v8 = v14--;
		if (!v8)
			break;
		a2 = calloc(1, sizeof(*a2));
		if (!a2)
			ft_error();
		a2->name = generate_name(maze);
		v9 = random_room(maze);
		create_tube(maze, v9, a2);
		add_room(maze, a2);
	}
}

t_room*
prev_room(t_room *room)
{
	return room->tubes->next->room;
}

void
generate_superpath(t_maze *maze, t_room *rsi0, int a3)
{
	int v3, v4;
	t_room *end, *a2;
	int i;
	t_room *v8;
	int v9;
	t_room *v10;

	v10 = rsi0;
	v9 = a3;
	for (i = 0; i != v9; ++i) {
		v8 = prev_room(v10);
		if (!(rand() % 2)) {
			a2 = maze->header->start;
			v3 = rand();
			generate_path(maze, a2, v10, v3 % 66 + v9 - i);
			end = maze->header->end;
			v4 = rand();
			generate_path(maze, v10, end, v4 % 66 + v9 - i);
		}
		v10 = v8;
	}
}

void
generate_superposition(t_maze *maze, t_room *start, t_room *end)
{
	int v3;
	int v4;
	t_room *v5;
	int v6;
	t_room *v7;
	int v8;
	t_room *rsi0;
	int a4;
	int v11;
	t_room *a3;

	a3 = end;
	v11 = rand() % 2 + 1;
	maze->start_ants = v11 * 4 * (rand() % 40 + 22);
	maze->field_8 = maze->start_ants;
	while (1) {
		v3 = v11--;
		if (!v3)
			break;
		v6 = rand() % 13;
		a4 = rand() % 9 + v6 + 32;
		rsi0 = generate_path(maze, start, a3, a4);
		generate_superpath(maze, rsi0, a4);
	}
	v8 = rand() % 220 + 20;
	while (1) {
		v4 = v8--;
		if (!v4)
			break;
		v7 = calloc(1, sizeof(*v7));
		if (!v7)
			ft_error();
		v7->name = generate_name(maze);
		v5 = random_room(maze);
		create_tube(maze, v5, v7);
		add_room(maze, v7);
	}
}

void
add_entry_exit(t_maze *maze, t_room *start, t_room *end)
{
	maze->header->start->name = generate_name(maze);
	maze->header->end->name = generate_name(maze);
	add_room(maze, end);
	add_room(maze, start);
}

void
lem_generate(t_maze *maze)
{
	unsigned int v1;
	t_room *start;
	t_room *end;

	create_header(maze);
	start = calloc(1, sizeof(*start));
	end = calloc(1, sizeof(*end));
	if (!start || !end)
		ft_error();
	maze->header->start = start;
	maze->header->end = end;
	v1 = time(0);// + clock();
	srand(v1);
	if (maze->gen_type) {
		switch (maze->gen_type) {
		case 1:
			generate_ten(maze, start, end);
			break;
		case 2:
			generate_thousand(maze, start, end);
			break;
		case 3:
			generate_big(maze, start, end);
			break;
		default:
			if (maze->gen_type != 4)
				ft_error();
			generate_superposition(maze, start, end);
			break;
		}
	} else {
		generate_one(maze, start, end);
	}
	add_entry_exit(maze, start, end);
}

t_room*
find_the_shortest(t_maze *maze, t_room *nodes)
{
	t_tube *v3;
	t_room *i;

	for (i = nodes; i; i = i->next) {
		v3 = i->tubes;
		if (i->field_18 && i->field_20 == maze->field_1C - 1) {
			while (v3) {
				if (v3->room == maze->header->end)
					return i;
				if (!v3->room->field_18) {
					v3->room->field_18 = 2LL;
					v3->room->field_28 = i;
					v3->room->field_20 = maze->field_1C;
				}
				v3 = v3->next;
			}
		}
	}
	return NULL;
}

void
put_back(t_maze *maze, t_room *a2)
{
	if (a2 != maze->header->tube_head) {
		a2->prev->next = a2->next;
		a2->next->prev = a2->prev;
		a2->next = NULL;
		maze->header->tube_head->next = a2;
		a2->prev = maze->header->tube_head;
		maze->header->tube_head = a2;
	}
}

int
re_distance(t_room *a1)
{
	if (a1->field_18 == 1)
		return 0;
	a1->field_24 = 2;
	a1->field_20 = re_distance(a1->field_28) + 1;
	return a1->field_20;
}

void
clear_maze(t_maze *maze, int a2)
{
	t_tube *v2;
	t_room *v3;

	v2 = maze->header->end->tubes;
	v3 = maze->header->tube_tail;
	if (!a2) {
		while (v2) {
			if (v2->room->field_24)
				re_distance(v2->room);
			v2 = v2->next;
		}
	}
	while (v3) {
		if (v3->field_18 != 1)
			v3->field_18 = 0LL;
		v3->field_24 = v3->field_24 == 2;
		v3->field_30 = 0LL;
		v3->field_38 = 0LL;
		v3 = v3->next;
	}
	maze->field_28 = 4LL;
}

void
lock_path(t_maze *maze, t_room *a2)
{
	t_room *a2a;

	a2a = a2;
	if (!a2)
		ft_error();
	put_back(maze, a2);
	while (a2a->field_18 != 1) {
		++maze->field_20;
		a2a->field_24 = 1;
		a2a = a2a->field_28;
	}
	maze->field_24 = maze->start_ants + maze->field_20;
	clear_maze(maze, 0);
}

void
processing(t_maze *maze)
{
	int v1;
	t_room *a2;

	maze->field_1C = 0;
	maze->total_nodes -= 2;
	do {
		v1 = maze->field_1C++;
		if (v1 > maze->total_nodes)
			break;
		a2 = find_the_shortest(maze, maze->header->tube_tail);
	} while (!a2);
	lock_path(maze, a2);
}

int
tube_len(t_tube *tube)
{
	int v2;
	t_tube *v3;

	v3 = tube;
	v2 = 0;
	while (v3) {
		++v2;
		v3 = v3->next;
	}
	return v2;
}

void
parse_negative_way(t_maze *maze, t_room *a2, t_room *a3, unsigned int a4)
{
	long long v4;
	int v5;
	t_room *v6;

	v5 = a4;
	if (a3->field_18 <= 2)
		v4 = maze->field_28;
	else
		v4= a3->field_18 | maze->field_28;
	a2->field_38 = a3;
	a2->field_30 = maze->field_28;
	a2->field_18 = -1LL;
	for (v6 = a2->field_28; v6->field_18 <= 0; v6 = v6->field_28) {
		put_back(maze, v6);
		v6->field_20 += v5;
		v6->field_18 = -v4;
	}
}

void
ft_normal(t_maze *a1, t_room *a2, t_room *a3, int a4)
{
	size_t v4;
	int v5;
	t_room *v6;

	v6 = a3;
	v5 = a4;
	if (a3->field_18 > 2)
		put_back(a1, a3);
	if (a2->field_18 == 1)
		v4 = 2LL;
	else
		v4 = a2->field_18;
	v6->field_18 = v4;
	v6->field_28 = a2;
	v6->field_20 = v5;
}

void
reverse_normal(t_maze *maze, t_room *a2, t_room *a3, unsigned int a4)
{
	ft_normal(maze, a2, a3, a4);
	a3->field_18 = -a3->field_18;
}

int alternative_path(t_maze*, t_room*, t_room*, unsigned);

int
draw_path(t_maze *maze, t_room *a2)
{
	t_tube *i;

	put_back(maze, a2);
	if (a2->field_20 == maze->field_1C)
		return 0;
	for (i = a2->tubes; i; i = i->next) {
		if (i->room == maze->header->end) {
			maze->field_28 = a2->field_18;
			maze->field_1C = a2->field_20;
			return 1;
		}
		if (!i->room->field_18) {
			if (i->room->field_24) {
				if (alternative_path(maze, i->room, a2, a2->field_20 - i->room->field_20 + 1))
					return 1;
			} else {
				reverse_normal(maze, a2, i->room, a2->field_20 + 1);
			}
		}
	}
	return 0;
}

int
alternative_path(t_maze *maze, t_room *a2, t_room *a3, unsigned int a4)
{
	int v4, v6;
	t_room *a2a;

	parse_negative_way(maze, a2, a3, a4);
	v6 = 0;
	maze->field_28 *= 2LL;
	while (1) {
		v4 = v6++;
		if (v4 >= maze->field_1C)
			break;
		for (a2a = maze->header->end->next; a2a; a2a = a2a->next) {
			if (a2a->field_18 < -1 && a2a->field_20 == v6) {
				a2a->field_18 = -a2a->field_18;
				if (draw_path(maze, a2a))
					return 1;
			}
		}
	}
	return 0;
}

int
new_path(t_maze *maze, t_room *start)
{
	int v2;
	t_tube *v4;
	t_room *a3;

	for (a3 = start; a3; a3 = a3->next) {
		v4 = a3->tubes;
		if (a3->field_18 > 0 && a3->field_20 == maze->field_1C - 1) {
			while (v4) {
				if (v4->room == maze->header->end) {
					v2 = a3->field_20;
					maze->field_1C = v2;
					if (v2) {
						maze->field_28 = a3->field_18;
						return 1;
					}
				}
				if (!v4->room->field_18) {
					if (v4->room->field_24) {
						if (alternative_path(maze, v4->room, a3, a3->field_20 - v4->room->field_20))
							return 1;
					} else {
						ft_normal(maze, a3, v4->room, maze->field_1C);
					}
				}
				v4 = v4->next;
			}
		}
	}
	return 0;
}

int
ascend(t_maze *maze, t_room *a2)
{
	int v3;
	t_room *v4;

	v4 = a2;
	v3 = 0;
	while (v4 != maze->header->start) {
		++v3;
		if (maze->field_28 & v4->field_30)
			v4 = v4->field_38;
		else
			v4 = v4->field_28;
	}
	return v3;
}

int
set_longest(t_maze *maze, int a2, int a3)
{
	int v4;

	v4 = maze->field_20;
	maze->field_20 = a2;
	return a3 * (a2 - v4);
}

int
score(t_maze *maze, int a2, int a3)
{
	int v4, v5;

	v5 = a2;
	v4 = maze->field_20 + 1;
	while (maze->start_ants > v5) {
		++v4;
		v5 += a3;
	}
	return v4;
}

int
build_path(t_maze *maze)
{
	int v2, a3, v4, a2, a2a;
	t_tube *v7;
	unsigned int v8;

	v7 = maze->header->end->tubes;
	a2 = a3 = v2 = 0;
	while (v7) {
		if (v7->room->field_24 || (v7->room->field_18 == maze->field_28 && v7->room->field_20 == maze->field_1C)) {
			if (v7->room->field_18 == maze->field_28 && v7->room->field_20 == maze->field_1C && v2) {
				v7->room->field_20 = 0;
			} else {
				v4 = ascend(maze, v7->room);
				if (v4 > maze->field_20)
					a2 += set_longest(maze, v4, a3);
				a2 += maze->field_20 - v4 + 1;
				++a3;
			}
			if (v7->room->field_18 == maze->field_28 && v7->room->field_20 == maze->field_1C)
				v2 = 1;
		}
		v7 = v7->next;
	}
	a2a = score(maze, a2, a3);
	if (maze->field_24 <= a2a) {
		v8 = 0;
	} else {
		maze->field_24 = a2a;
		v8 = a2a;
	}
	return v8;
}

int
lock_path_new(t_maze *maze, t_room *a2)
{
	unsigned int v3;

	if (a2 == maze->header->start) {
		v3 = 0;
	} else {
		a2->field_24 = 2;
		if (maze->field_28 & a2->field_30)
			a2->field_28 = a2->field_38;
		a2->field_20 = lock_path_new(maze, a2->field_28) + 1;
		v3 = a2->field_20;
	}
	return v3;
}

void
create_new_paths(t_maze *maze, t_tube *a2)
{
	t_tube *i;

	for (i = a2; i; i = i->next) {
		if (i->room->field_24 || (i->room->field_18 == maze->field_28 && maze->field_1C == i->room->field_20))
			lock_path_new(maze, i->room);
	}
}

int
lock_path_other(t_maze *maze)
{
	int v2;

	if (build_path(maze)) {
		create_new_paths(maze, maze->header->end->tubes);
		clear_maze(maze, 1);
		v2 = 1;
	} else {
		clear_maze(maze, 0);
		v2 = 0;
	}
	return v2;
}

int
find_another_path(t_maze *maze)
{
	int v1;

	maze->field_1C = 0;
	while (1) {
		v1 = maze->field_1C++;
		if (v1 > maze->total_nodes)
			break;
		if (new_path(maze, maze->header->start))
			return lock_path_other(maze);
	}
	return 0;
}

void
find_best_combination(t_maze *maze)
{
	int etl, stl;

	stl = tube_len(maze->header->start->tubes);
	etl = tube_len(maze->header->end->tubes);
	if (etl < stl)
		stl = etl;
	do {
		--stl;
	} while (stl && find_another_path(maze));
}

void
forward_ants(t_maze *maze, t_room *a2, int a3)
{
	t_room *v3;

	v3 = a2;
	if (a2->field_10) {
		++maze->field_C;
		a2->field_10 = 0;
	}
	while (v3->field_18 != 1) {
		if (v3->field_28->field_10) {
			v3->field_10 = v3->field_28->field_10;
			v3->field_28->field_10 = 0;
		}
		if (a3 && v3->field_28->field_18 == 1) {
			if (maze->field_8)
				v3->field_10 = maze->start_ants - --maze->field_8;
		}
		v3 = v3->field_28;
	}
}

int
count_lines(t_maze *maze)
{
	int lines;
	t_tube *tube;

	lines = 0;
	while (maze->field_C != maze->start_ants) {
		for (tube = maze->header->end->tubes; tube; tube = tube->next) {
			if (tube->room->field_24)
				forward_ants(maze, tube->room, lines + tube->room->field_20 < maze->field_24);
		}
		lines += 1;
	}
	return lines;
}

int
algorithm(t_maze *maze)
{
	processing(maze);
	find_best_combination(maze);
	return count_lines(maze);
}

unsigned int
print_room(t_room *a1, int a2)
{
	int v2, v4, v5;
	unsigned int v6;
	t_room *a1a;
	unsigned int v8;

	if (a1) {
		if (rand() % 2) {
			printf("%s %u %u\n", a1->name, a2, a2);
			a1a = a1->next;
			v6 = rand() % 3 + a2;
			v2 = rand();
			v8 = print_room(a1a, v2 % 3 + v6 + 1);
		} else {
			v5 = print_room(a1->next, a2);
			v4 = rand() % 3 + v5;
			v8 = rand() % 3 + v4 + 1;
			printf("%s %u %u\n", a1->name, v8, v8);
		}
	} else {
		v8 = a2;
	}
	return v8;
}

void
print_link(t_link *a1)
{
	if (a1) {
		if (rand() % 2) {
			printf("%s-%s\n", a1->src->name, a1->dst->name);
			print_link(a1->next);
		} else {
			print_link(a1->next);
			printf("%s-%s\n", a1->src->name, a1->dst->name);
		}
	}
}

void
print_map(t_maze *maze)
{
	int v1, v3;
	t_room *a1a;
	int v5, v6, v7, v8;

	printf("%d\n", maze->start_ants);
	printf("#Here is the number of lines required: %d\n", maze->algo_ret);
	v6 = rand() % 3;
	v7 = rand() % 3 + v6;
	printf("##start\n%s %u %u\n", maze->header->start->name, v7, v7);
	v5 = rand() % 3;
	v8 = v7 + rand() % 3 + v5 + 1;
	printf("##end\n%s %u %u\n", maze->header->end->name, v8, v8);
	a1a = maze->header->tube_tail->next->next;
	v3 = rand() % 3 + v8;
	v1 = rand();
	print_room(a1a, v1 % 3 + v3 + 1);
	print_link(maze->links);
	printf("#Here is the number of lines required: %d\n", maze->algo_ret);
}

void
lemin(int opt)
{
	t_maze maze;

	bzero(&maze, sizeof(maze));
	maze.gen_type = opt;
	lem_generate(&maze);
	maze.algo_ret = algorithm(&maze);
	print_map(&maze);
	exit(0);
}

int
main(int argc, const char *argv[])
{
	lemin(lem_options(argc, argv));
}