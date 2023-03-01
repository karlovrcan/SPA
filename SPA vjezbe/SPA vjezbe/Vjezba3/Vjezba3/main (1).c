#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _coordinate {
	float x;
	float z;
	float y;
}coordinate;

typedef struct _triangle {
	coordinate normal;
	coordinate coordinates[3];
	unsigned short color;
}triangle;

typedef struct _object3D {
	triangle* triangles;
	unsigned int count;
}Object3D;

// void readOBJfromBinary(char* filename, Object3D* stl);
// void writeBinaryFromSTL(Object3D* stl);
// void writeTxtFromSTL(Object3D* stl);
// void freeSTL(Object3D* stl); 

void readOBJfromBinary(char* filename, Object3D* stl)
{
	FILE* f;
	coordinate temp;

	unsigned int countOfTriangles;
	f = fopen(filename, "rb"); 

	stl = (Object3D*)malloc(sizeof(stl));
	fseek(f, 80, SEEK_SET);
	fread(&countOfTriangles, 4, 1, f);
	stl->count = countOfTriangles;
	stl->triangles = (triangle*)malloc(stl->count * sizeof(triangle));

	int i = 0, j = 0;
	for (i = 0; i < stl->count; i++)
	{
		fread(&temp.x, 4, 1, f);
		fread(&temp.y, 4, 1, f);
		fread(&temp.z, 4, 1, f);
		stl->triangles[i].normal.x = temp.x;
		stl->triangles[i].normal.y = temp.y;
		stl->triangles[i].normal.z = temp.z;

		fread(&temp.x, 4, 1, f);
		fread(&temp.y, 4, 1, f);
		fread(&temp.z, 4, 1, f);
		stl->triangles[i].coordinates[j].x = temp.x;
		stl->triangles[i].coordinates[j].y = temp.y;
		stl->triangles[i].coordinates[j].z = temp.z;
		j++;

		fread(&temp.x, 4, 1, f);
		fread(&temp.y, 4, 1, f);
		fread(&temp.z, 4, 1, f);
		stl->triangles[i].coordinates[j].x = temp.x;
		stl->triangles[i].coordinates[j].y = temp.y;
		stl->triangles[i].coordinates[j].z = temp.z;
		j++;

		fread(&temp.x, 4, 1, f);
		fread(&temp.y, 4, 1, f);
		fread(&temp.z, 4, 1, f);
		stl->triangles[i].coordinates[j].x = temp.x;
		stl->triangles[i].coordinates[j].y = temp.y;
		stl->triangles[i].coordinates[j].z = temp.z;

		j = 0;
		fseek(f, 2, SEEK_CUR);
	}
	fclose(f);

	writeBinaryFromSTL(stl);
	writeTxtFromSTL(stl);
	freeSTL(stl);
}

void writeBinaryFromSTL(Object3D* stl)
{
	FILE* f = fopen("newSTLbinary.stl", "wb");
	int i = 0, j = 0;
	uint8_t zeros[80];
	for (i = 0; i < 80; i++)
		zeros[i] = 0;
	fwrite(&zeros, 80, 1, f);
	unsigned int count = stl->count;
	fwrite(&count, 4, 1, f);
	unsigned short color = 0;

	for (i = 0; i < stl->count; i++)
	{
		//normal
		fwrite(&stl->triangles[i].normal.x, 4, 1, f);
		fwrite(&stl->triangles[i].normal.y, 4, 1, f);
		fwrite(&stl->triangles[i].normal.z, 4, 1, f);

		//triangle
		fwrite(&stl->triangles[i].coordinates[j].x, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].y, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].z, 4, 1, f);
		j++;

		fwrite(&stl->triangles[i].coordinates[j].x, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].y, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].z, 4, 1, f);
		j++;

		fwrite(&stl->triangles[i].coordinates[j].x, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].y, 4, 1, f);
		fwrite(&stl->triangles[i].coordinates[j].z, 4, 1, f);
		fwrite(&color, 2, 1, f);

		j = 0;
	}
	fclose(f);
}

void writeTxtFromSTL(Object3D* stl)
{
	FILE* f = fopen("newSTLtxt.stl", "w");
	int i = 0, j = 0;
	for (i = 0; i < stl->count; i++)
	{
		fprintf(f, "\tfacet normal %f %f %f\n", stl->triangles[i].normal.x, stl->triangles[i].normal.y, stl->triangles[i].normal.z);
		fprintf(f, "\t\touter loop\n\t\t\tvertex %f %f %f\n", stl->triangles[i].coordinates[j].x, stl->triangles[i].coordinates[j].y, stl->triangles[i].coordinates[j].z);
		j++;
		fprintf(f, "\t\t\tvertex %f %f %f\n", stl->triangles[i].coordinates[j].x, stl->triangles[i].coordinates[j].y, stl->triangles[i].coordinates[j].z);
		j++;
		fprintf(f, "\t\t\tvertex %f %f %f\n\t\tendloop\n\tendfacet\n", stl->triangles[i].coordinates[j].x, stl->triangles[i].coordinates[j].y, stl->triangles[i].coordinates[j].z);
		j = 0;
	}
	fclose(f);
}

void freeSTL(Object3D* stl) 
{
	free(stl);
}

int main()
{
	char* filename = "primjerbin.stl";
	Object3D* stl = NULL;
	readOBJfromBinary(filename, stl);
	return 0;
}