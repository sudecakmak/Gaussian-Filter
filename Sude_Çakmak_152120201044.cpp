#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <ctime>     

#define FILTERSIZE 100
#define max 100

using namespace std;

int main()
{
	ifstream infile;
	ofstream outputfile;

	double kernel[FILTERSIZE][FILTERSIZE] = { 0 };
	int d, i, j, f, k, l, g, h, p, q;
	double value, sum = 0;
	int image_size, filter_size, mirror_size;
	int whitePixelValue, blackPixelValue;
	double input_image[max][max], input_grid[max][max];
	double mirrored_image[max][max], output[max][max], multiplication[max][max];

	srand(time(NULL));

	cout.setf(ios::fixed);
	cout.precision(4);

	outputfile << fixed << showpoint;
	outputfile << setprecision(4);

	infile.open("inputs.txt");
	outputfile.open("output.txt");

	if (!infile)
	{
		cout << "Cannot open the input file.";
		return 1;
	}

	infile >> image_size >> filter_size >> whitePixelValue >> blackPixelValue;

	cout << "Processing data..." << "\n\n\n";

	cout << "Input Image (" << image_size << "x" << image_size << ")" << endl;
	outputfile << "Input Image (" << image_size << "x" << image_size << ")" << endl;

	for (k = 0; k < (9 * image_size); k++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	for (i = 0; i < image_size; i++)
	{
		for (j = 0; j < image_size; j++)
		{
			input_image[i][j] = (rand() % (whitePixelValue - blackPixelValue + 1)) + blackPixelValue;

			cout << right << setw(9) << input_image[i][j];
			outputfile << right << setw(9) << input_image[i][j];
		}

		cout << endl;
		outputfile << endl;
	}

	for (i = 0; i < (9 * image_size); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	f = filter_size / 2;

	for (d = 0; d < f; d++)
	{
		value = 1.0 / pow((2 * (d + 1) + 1), 2);

		for (i = -(d + 1); i <= d + 1; i++)
		{
			for (j = -(d + 1); j <= d + 1; j++)
				kernel[f - i][f - j] = kernel[f - i][f - j] + value;
		}
	}

	for (i = 0; i < filter_size; i++)
	{
		for (j = 0; j < filter_size; j++)
		{
			kernel[i][j] = kernel[i][j] / static_cast<double>(filter_size);
		}
	}

	cout << "\n\n";

	cout << "Gaussian Filter (" << filter_size << "x" << filter_size << ")" << endl;
	outputfile << "Gaussian Filter (" << filter_size << "x" << filter_size << ")" << endl;

	for (i = 0; i < (9 * filter_size); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	for (i = 0; i < filter_size; i++)
	{
		for (j = 0; j < filter_size; j++)
		{
			cout << right << setw(9) << kernel[i][j];
			outputfile << right << setw(9) << kernel[i][j];
		}

		cout << endl;
		outputfile << endl;
	}

	for (i = 0; i < (9 * filter_size); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	cout << "\n\n";

	mirror_size = filter_size / 2;

	p = 0;
	q = image_size;

	while (mirror_size != p)
	{
		p++;

		for (k = 0; k < (q + 2); k++)
		{
			for (l = 0; l < (q + 2); l++)
			{
				i = k - 1;
				j = l - 1;

				if (k == 0)
				{
					i = k;
				}
				if (l == (q + 2) - 1)
				{
					j = l - 2;
				}
				if (k == (q + 2) - 1)
				{
					i = k - 2;
				}
				if (l == 0)
				{
					j = l;
				}

				mirrored_image[k][l] = input_image[i][j];

			}
		}

		for (k = 0; k < (q + 2); k++)
		{
			for (l = 0; l < (q + 2); l++)
			{
				input_image[k][l] = mirrored_image[k][l];
			}
		}

		q = q + 2;

	}

	q = q - 2;

	cout << "Input Grid: Edge Mirrored Image (21x21)" << endl;
	outputfile << "Input Grid: Edge Mirrored Image (21x21)" << endl;

	for (i = 0; i < (9 * 21); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			if (i < ((21 - (image_size + mirror_size * 2)) / 2) || j < ((21 - (image_size + mirror_size * 2)) / 2))
			{
				input_grid[i][j] = 0;
				cout << right << setw(9) << input_grid[i][j];
				outputfile << right << setw(9) << input_grid[i][j];
			}
			else if (i > (21 - ((21 - (image_size + mirror_size * 2)) / 2) - 1) || j > (21 - ((21 - (image_size + mirror_size * 2)) / 2) - 1))
			{
				input_grid[i][j] = 0;
				cout << right << setw(9) << input_grid[i][j];
				outputfile << right << setw(9) << input_grid[i][j];
			}
			else
			{
				k = i - ((21 - (image_size + mirror_size * 2)) / 2);
				l = j - ((21 - (image_size + mirror_size * 2)) / 2);
				cout << right << setw(9) << mirrored_image[k][l];
				outputfile << right << setw(9) << mirrored_image[k][l];
			}
		}

		cout << endl;
		outputfile << endl;
	}

	for (i = 0; i < (9 * 21); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl << endl << endl;
	outputfile << endl;

	g = 0;
	h = 0;

	for (k = 0; k < image_size; k++)
	{
		for (l = 0; l < image_size; l++)
		{

			for (i = 0; i < filter_size; i++)
			{
				for (j = 0; j < filter_size; j++)
				{
					g = k + i;
					h = l + j;

					multiplication[i][j] = mirrored_image[g][h] * kernel[i][j];
				}
			}

			for (i = 0; i < filter_size; i++)
			{
				for (j = 0; j < filter_size; j++)
				{
					sum = sum + multiplication[i][j];
				}
			}

			sum = sum / pow(filter_size, 2);

			output[k][l] = sum;

			sum = 0;
		}
	}

	cout << "Output Grid: Cutted-Edge Image (21x21)" << endl;
	outputfile << "Output Grid: Cutted-Edge Image (21x21)" << endl;

	for (i = 0; i < (9 * 21); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			if (i < ((21 - image_size) / 2) || j < ((21 - image_size) / 2))
			{
				input_grid[i][j] = 0;
				cout << right << setw(9) << input_grid[i][j];
				outputfile << right << setw(9) << input_grid[i][j];
			}
			else if (i > (21 - ((21 - image_size) / 2) - 1) || j > (21 - ((21 - image_size) / 2) - 1))
			{
				input_grid[i][j] = 0;
				cout << right << setw(9) << input_grid[i][j];
				outputfile << right << setw(9) << input_grid[i][j];
			}
			else
			{
				k = i - ((21 - image_size) / 2);
				l = j - ((21 - image_size) / 2);
				cout << right << setw(9) << output[k][l];
				outputfile << right << setw(9) << output[k][l];
			}
		}

		cout << endl;
		outputfile << endl;
	}

	for (i = 0; i < (9 * 21); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl << endl << endl;
	outputfile << endl;


	cout << "Output (Filtered) Image (" << image_size << "x" << image_size << ")" << endl;
	outputfile << "Output (Filtered) Image (" << image_size << "x" << image_size << ")" << endl;

	for (k = 0; k < (9 * image_size); k++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	for (i = 0; i < image_size; i++)
	{
		for (j = 0; j < image_size; j++)
		{
			cout << right << setw(9) << output[i][j];
			outputfile << right << setw(9) << output[i][j];
		}

		cout << endl;
		outputfile << endl;
	}

	for (i = 0; i < (9 * image_size); i++)
	{
		cout << "-";
		outputfile << "-";
	}

	cout << endl;
	outputfile << endl;

	infile.close();
	outputfile.close();

	system("pause");
	return 0;
}
