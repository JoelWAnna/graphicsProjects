#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "test.h"
using namespace std;
typedef std::pair<std::string,std::string> strpair;
typedef std::pair<std::string, std::vector<strpair>> type;
std::vector<type> setuptests(int x);
void Compare(strpair tocompare);
void test(int x)
{
	std::vector<type> tests = setuptests(x);

	for (int i = 0; i < tests.size(); ++i)
	{
		std::cout << "running test" << tests.at(i).first << std::endl;
		for (int j = 0; j < tests.at(i).second.size(); ++j)
		{
			strpair temp = tests.at(i).second.at(j);
			Compare(temp);
		}
	}
}
void Compare(strpair tocompare)
{
	FILE* a = fopen(tocompare.first.c_str(), "rb");
	FILE* b = fopen(tocompare.second.c_str(), "rb");
	FILE* c = nullptr;
	if (!a || !b)
	{
		std::cout << "missing file" << tocompare.first << std::endl;
	}
	fseek(a, 0, SEEK_END);
	fseek(b, 0, SEEK_END);
	int size = ftell(a);
	if (size != ftell(b))
	{
		std::cout << "invalid size" << tocompare.first << std::endl;
		return;
	}
	fseek(a, 0x27, SEEK_SET);
	fseek(b, 0x27, SEEK_SET);
	int pixels = (size-0x27)/4;
	int *bufferA = new int[pixels];
	int *bufferB = new int[pixels];
	fread((void*)bufferA, 4, pixels, a);
	fread((void*)bufferB, 4, pixels, b);

	int errors = 0;
	int root = sqrt((float)pixels);
	for (int i = 0; i < root; ++i)
	{
		
		for (int j = 0; j < root; ++j)
		{
		if (bufferA[i*root+j] != bufferB[i*root+j])
		{
			if (!c)
			{
				c = fopen((tocompare.first + ".log").c_str(), "w");
				char buffer[1024];
				sprintf(buffer,"size is %d",root);
				fwrite(buffer, strlen(buffer), 1, c);
			}

			if (c)
			{
				
				char buffer[1024];
				sprintf(buffer,"x = %d, y = %d, Expected %x, actual %x\n", j, root -1- i, bufferB[i*root+j], bufferA[i*root+j]);
				fwrite(buffer, strlen(buffer), 1, c);
			//	std::cout << std::hex << bufferA[i] << " " << bufferB[i] << std::endl;
			}
			errors++;
		}
		}
	}
	delete [] bufferA;
	delete [] bufferB;
	std::cout << errors << " errors in file " << tocompare.first << std::endl;
	fclose(a);
	fclose(b);
	if (c) fclose(c);
}

std::vector<type> setuptests(int x)
{
	std::vector<type> tests;

	std::vector<strpair> files;


	// CURRENTLY WORKING
	if (x & T_COMP)
	{
	files.push_back(strpair("zcolorcheck-comp-atop.tga","zcolorcheck-comp-atop_EXPECTED.tga"));
	files.push_back(strpair("zcolorcheck-comp-in.tga","zcolorcheck-comp-in_EXPECTED.tga"));
	files.push_back(strpair("zcolorcheck-comp-out.tga","zcolorcheck-comp-out_EXPECTED.tga"));
	files.push_back(strpair("zcolorcheck-comp-over.tga","zcolorcheck-comp-over_EXPECTED.tga"));
	files.push_back(strpair("zcolorcheck-comp-xor.tga","zcolorcheck-comp-xor_EXPECTED.tga"));
	tests.push_back(type("comp", files));
	files.clear();
	}
	
	if (x & T_QUANT_UNIF)
	{
	files.push_back(strpair("church-quant-unif.tga","church-quant-unif_EXPECTED.tga"));
	files.push_back(strpair("wiz-quant-unif.tga","wiz-quant-unif_EXPECTED.tga"));
	tests.push_back(type("quant-unif", files));
	files.clear();
	}

	if (x & T_FILTBARLET)
	{
		files.push_back(strpair("checkers-filter-bartlett.tga", "checkers-filter-bartlett_EXPECTED.tga"));
		files.push_back(strpair("church-filter-bartlett.tga","church-filter-bartlett_EXPECTED.tga"));
	tests.push_back(type("filter-barlett", files));
	files.clear();
	}

	if (x & T_FILT_BOX)
	{
		files.push_back(strpair("checkers-filter-box.tga","checkers-filter-box_EXPECTED.tga"));
	files.push_back(strpair("church-filter-box.tga","church-filter-box_EXPECTED.tga"));
	tests.push_back(type("filter-box", files));
	files.clear();
	}
	if (x & T_FILT_ENHANCE)
	{
	
	files.push_back(strpair("checkers-filter-enhance.tga","checkers-filter-enhance_EXPECTED.tga"));
	files.push_back(strpair("church-filter-enhance.tga","church-filter-enhance_EXPECTED.tga"));
	tests.push_back(type("filter-enhance", files));
	files.clear();
	}
	if (x & T_FILT_GAUSS_N)
	{
	
	files.push_back(strpair("church-filter-gauss-n.tga","church-filter-gauss-n_EXPECTED.tga"));
	files.push_back(strpair("checkers-filter-gauss-n.tga","checkers-filter-gauss-n_EXPECTED.tga"));
	tests.push_back(type("filter-gauss-n", files));
	files.clear();
		}
	if (x & T_FILT_GAUSS)
	{
	
	files.push_back(strpair("checkers-filter-gauss.tga","checkers-filter-gauss_EXPECTED.tga"));
	files.push_back(strpair("church-filter-gauss.tga","church-filter-gauss_EXPECTED.tga"));
	tests.push_back(type("filter-gauss", files));
	files.clear();
	}
	if (x & T_FILT_EDGE)
	{
	

	files.push_back(strpair("checkers-filter-edge.tga","checkers-filter-edge_EXPECTED.tga"));
	files.push_back(strpair("church-filter-edge.tga","church-filter-edge_EXPECTED.tga"));
	files.push_back(strpair("gray-checkers-filter-edge.tga","gray-checkers-filter-edge_EXPECTED.tga"));
	tests.push_back(type("filter-edge", files));
	files.clear();
	}
	
	if (x & T_FILT_ENHANCE)
	{
	files.push_back(strpair("gray-checkers-filter-enhance.tga","gray-checkers-filter-enhance_EXPECTED.tga"));
	tests.push_back(type("filter-enhance", files));
	files.clear();
	}

	if (x & T_QUANT_POP)
	{
	files.push_back(strpair("church-quant-pop.tga","church-quant-pop_EXPECTED.tga"));
	files.push_back(strpair("wiz-quant-pop.tga","wiz-quant-pop_EXPECTED.tga"));
	tests.push_back(type("quant-pop", files));
	files.clear();
	
	}

	if (x & T_DITHER_BRIGHT)
	{

	files.push_back(strpair("church-dither-bright.tga","church-dither-bright_EXPECTED.tga"));
	tests.push_back(type("dither-bright", files));
	files.clear();
	}
	

	if (x & 0)
	{
	files.push_back(strpair("church-dither-color.tga","church-dither-color_EXPECTED.tga"));
	//tests.push_back(type("dither-color", files));
	files.clear();
	}
	

	if (x & T_DITHER_FS)
	{
	files.push_back(strpair("church-dither-fs.tga","church-dither-fs_EXPECTED.tga"));
	tests.push_back(type("dither-fs", files));
	files.clear();
	}

	if (x & T_DITHER_CLUST)
	{
	files.push_back(strpair("church-dither-cluster.tga","church-dither-cluster_EXPECTED.tga"));
	tests.push_back(type("dither-cluster", files));
	files.clear();

	}
	if (x & T_DITHER_RAND)
	{
	files.push_back(strpair("church-dither-rand.tga","church-dither-rand_EXPECTED.tga"));
	tests.push_back(type("dither-rand", files));
	files.clear();
	}
	if (x & T_DITHER_THRESH)
	{
	files.push_back(strpair("church-dither-thresh.tga","church-dither-thresh_EXPECTED.tga"));
	tests.push_back(type("dither-thresh", files));
	files.clear();
	}
	if (x & T_HALF)
	{
	files.push_back(strpair("church-half.tga","church-half_EXPECTED.tga"));
	files.push_back(strpair("checkers-half.tga","checkers-half_EXPECTED.tga"));
	tests.push_back(type("half", files));
	files.clear();
	}

	if (x & T_ROTATE)
	{
	files.push_back(strpair("church-rotate.tga","church-rotate_EXPECTED.tga"));
	files.push_back(strpair("checkers-rotate.tga","checkers-rotate_EXPECTED.tga"));
	tests.push_back(type("rotate", files));
	files.clear();
	}

	if (x & T_SCALE)
	{

	files.push_back(strpair("church-scale.tga","church-scale_EXPECTED.tga"));
	files.push_back(strpair("checkers-scale.tga","checkers-scale_EXPECTED.tga"));
	tests.push_back(type("scale", files));
	files.clear();
	}

	if (x & T_DOUBLE)
	{

	files.push_back(strpair("church-small-double.tga","church-small-double_EXPECTED.tga"));
	files.push_back(strpair("checkers-small-double.tga","checkers-small-double_EXPECTED.tga"));
	tests.push_back(type("double", files));
	files.clear();
	
	}

	if (x & T_NPR)
	{
	files.push_back(strpair("wiz-npr-paint.tga","wiz-npr-paint_EXPECTED.tga"));
	files.push_back(strpair("church-npr-paint.tga","church-npr-paint_EXPECTED.tga"));
	tests.push_back(type("npr-paint", files));
	files.clear();
	}
	
	if (x & T_GRAY)
	{
	files.push_back(strpair("colors-for-bw-gray.tga","colors-for-bw-gray_EXPECTED.tga"));
		tests.push_back(type("gray", files));
	files.clear();
	}

	


return tests;
}


void writescript(int x)
{
	std::ofstream file;
	file.open("script.txt", ios_base::out|ios_base::trunc);

	// CURRENTLY WORKING
	if (x & T_COMP)
	{
		file << "load zcolorcheck.tga" << endl;
		file << "comp-over zred.tga" << endl;
		file << "save zcolorcheck-comp-over.tga" << endl;
		file << "load zcolorcheck.tga" << endl;
		file << "comp-in zred.tga" << endl;
		file << "save zcolorcheck-comp-in.tga" << endl;
		file << "load zcolorcheck.tga" << endl;
		file << "comp-out zred.tga" << endl;
		file << "save zcolorcheck-comp-out.tga" << endl;
		file << "load zcolorcheck.tga" << endl;
		file << "comp-atop zred.tga" << endl;
		file << "save zcolorcheck-comp-atop.tga" << endl;
		file << "load zcolorcheck.tga" << endl;
		file << "comp-xor zred.tga" << endl;
		file << "save zcolorcheck-comp-xor.tga" << endl;
	}
	
	if (x & T_QUANT_UNIF)
	{
		file << "load church.tga" << endl;
		file << "quant-unif" << endl;
		file << "save church-quant-unif.tga" << endl;
		file << "load wiz.tga" << endl;
		file << "quant-unif" << endl;
		file << "save wiz-quant-unif.tga" << endl;
	}

	if (x & T_FILTBARLET)
	{
		file << "load church.tga" << endl;
		file << "filter-bartlett" << endl;
		file << "save church-filter-bartlett.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "filter-bartlett" << endl;
		file << "save checkers-filter-bartlett.tga" << endl;
	}

	if (x & T_FILT_BOX)
	{
		file << "load church.tga" << endl;
		file << "filter-box" << endl;
		file << "save church-filter-box.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "filter-box" << endl;
		file << "save checkers-filter-box.tga" << endl;
	}
	if (x & T_FILT_ENHANCE)
	{
		file << "load church.tga" << endl;
		file << "filter-enhance" << endl;
		file << "save church-filter-enhance.tga" << endl;

		file << "load checkers.tga" << endl;
		file << "filter-enhance" << endl;
		file << "save checkers-filter-enhance.tga" << endl;
		
		file << "load gray-checkers.tga" << endl;
		file << "filter-enhance" << endl;
		file << "save gray-checkers-filter-enhance.tga" << endl;
	}
	if (x & T_FILT_GAUSS_N)
	{		
		file << "load church.tga" << endl;
		file << "filter-gauss-n 9" << endl;
		file << "save church-filter-gauss-n.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "filter-gauss-n 11" << endl;
		file << "save checkers-filter-gauss-n.tga" << endl;
	}
	if (x & T_FILT_GAUSS)
	{
		file << "load church.tga" << endl;
		file << "filter-gauss" << endl;
		file << "save church-filter-gauss.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "filter-gauss" << endl;
		file << "save checkers-filter-gauss.tga" << endl;
	}
	if (x & T_FILT_EDGE)
	{
		file << "load church.tga" << endl;
		file << "filter-edge" << endl;
		file << "save church-filter-edge.tga" << endl;

		file << "load checkers.tga" << endl;
		file << "filter-edge" << endl;
		file << "save checkers-filter-edge.tga" << endl;

		file << "load gray-checkers.tga" << endl;
		file << "filter-edge" << endl;
		file << "save gray-checkers-filter-edge.tga" << endl;
	}
	

	if (x & T_QUANT_POP)
	{
		file << "load church.tga" << endl;
		file << "quant-pop" << endl;
		file << "save church-quant-pop.tga" << endl;
		
		file << "load wiz.tga" << endl;
		file << "quant-pop" << endl;
		file << "save wiz-quant-pop.tga" << endl;
	
	}

	if (x & T_DITHER_BRIGHT)
	{

		file << "load church.tga" << endl;
		file << "dither-bright" << endl;
		file << "save church-dither-bright.tga" << endl;
	}
	

	if (x & 0)
	{
	//files.push_back(strpair("church-dither-color.tga","church-dither-color_EXPECTED.tga"));
	//tests.push_back(type("dither-color", files));
	}
	

	if (x & T_DITHER_FS)
	{
		file << "load church.tga" << endl;
		file << "dither-fs" << endl;
		file << "save church-dither-fs.tga" << endl;
	}

	if (x & T_DITHER_CLUST)
	{
		file << "load church.tga" << endl;
		file << "dither-cluster" << endl;
		file << "save church-dither-cluster.tga" << endl;

	}
	if (x & T_DITHER_RAND)
	{
		file << "load church.tga" << endl;
		file << "dither-rand" << endl;
		file << "save church-dither-rand.tga" << endl;
	}
	if (x & T_DITHER_THRESH)
	{
		file << "load church.tga" << endl;
		file << "dither-thresh" << endl;
		file << "save church-dither-thresh.tga" << endl;
	}
	if (x & T_HALF)
	{
		file << "load church.tga" << endl;
		file << "half" << endl;
		file << "save church-half.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "half" << endl;
		file << "save checkers-half.tga" << endl;
	}

	if (x & T_ROTATE)
	{
		file << "load church.tga" << endl;
		file << "rotate 30" << endl;
		file << "save church-rotate.tga" << endl;

		file << "load checkers.tga" << endl;
		file << "rotate 75" << endl;
		file << "save checkers-rotate.tga" << endl;
		
	}

	if (x & T_SCALE)
	{
		file << "load church.tga" << endl;
		file << "scale 0.8" << endl;
		file << "save church-scale.tga" << endl;
		
		file << "load checkers.tga" << endl;
		file << "scale 1.5" << endl;
		file << "save checkers-scale.tga" << endl;
		
	}

	if (x & T_DOUBLE)
	{
		file << "load church-small.tga" << endl;
		file << "double" << endl;
		file << "save church-small-double.tga" << endl;
		
		file << "load checkers-small.tga" << endl;
		file << "double" << endl;
		file << "save checkers-small-double.tga" << endl;	
	}

	if (x & T_NPR)
	{
		file << "load church.tga" << endl;
		file << "npr-paint" << endl;
		file << "save church-npr-paint.tga" << endl;
		
		file << "load wiz.tga" << endl;
		file << "npr-paint" << endl;
		file << "save wiz-npr-paint.tga" << endl;
	}
	
	if (x & T_GRAY)
	{
		file << "load colors-for-bw.tga" << endl;
		file << "gray" << endl;
		file << "save colors-for-bw-gray.tga" << endl;
		
	}

		

	file << "test " << x << endl;
	file.flush();
	file.close();
	cout << "wrote" << x << endl;
}