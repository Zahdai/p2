#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct coord {
	double x;
	double y;
	double z;
};

struct point {
	double w; //weight
	struct coord xyz;
} typedef point;

int findMinWInd(point *arr, int len) {
	int i, minWInd = 0;
	double minW = arr[0].w;
	for (i = 1; i < len; i++)
		if (arr[i].w < minW) {
			minW = arr[i].w;
			minWInd = i;
		}
	return minWInd;
}

void fuseWithClosest(point *arr, int len, int ind) {
	if (len == 1)
		return;
	double x = arr[ind].xyz.x, y = arr[ind].xyz.y, z = arr[ind].xyz.z;
	//составляем массив расстояний от нашей точки
	double dists[len];
	int i;
	for (i = 0; i < len; i++) {
		if (i == ind)
			continue;
		double dist = sqrt( pow(arr[i].xyz.x-x, 2) + pow(arr[i].xyz.y-y, 2) +
			pow(arr[i].xyz.z-z, 2));
		dists[i] = dist;
	}
	//выбираем из расстояний наименьшее
	int minDistInd = ind == 0? 1: 0;
	double minDist = dists[ minDistInd];
	for (i = 1; i < len; i++)
		if (i == ind)
			continue;
		else if (dists[i] < minDist) {
			minDist = dists[i];
			minDistInd = i;
		}
	//переносим массу точки
	arr[ minDistInd].w += arr[ind].w;
	//уменьшаем массив
	for (; ind < len-1; ind++)
		arr[ind] = arr[ind+1];
}

int main(int args, char *argv[]) {
	if (args == 1) {
		printf("Type n as an argument\n");
		return 1;
	}
	int plength = atoi(argv[1]);
	point points[ plength];
	printf("Type points in format (x y z w)\n");
	int i;
	for (i = 0; i < plength; i++) {
		printf("P%d: ", i);
		scanf("%lf %lf %lf %lf", &points[i].xyz.x, &points[i].xyz.y,
		&points[i].xyz.z, &points[i].w);
	}
	while (plength > 1) {
		int minWPointInd = findMinWInd(points, plength);
		point minWP = points[ minWPointInd];
		printf("The smallest point:\nP%d (%f,%f,%f): w=%f\n", minWPointInd,
		minWP.xyz.x, minWP.xyz.y, minWP.xyz.z, minWP.w);
		fuseWithClosest( points, plength, minWPointInd);
		plength--;
		printf("The points was fused:\n");
		for (i = 0; i < plength; i++)
			printf("P%d (%f,%f,%f): w=%f\n", i, points[i].xyz.x,
				points[i].xyz.y, points[i].xyz.z, points[i].w);
		getchar();
		getchar();
	}
	return 0;
}
