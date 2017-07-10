/*
* ECG.h
* 
* VARPA, University of Coruña
* Mondejar Guerra, Victor M.
* 29 Jun 2017
*/

// ECG.h
#ifndef ECG_H
#define ECG_H

#include "libsvm-3.22/svm.h"
#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include <stdlib.h>  
#include <vector>
#include "QRS_detection.h"

class ECG {

	public:
		//Constructor
		ECG(std::string svm_model_name, int w_l, int w_r, bool u_RR_i, bool u_w);

		void predict_ecg(std::vector<float> ecg, float fs, float minA, float maxA,
                    float n_bits, std::string output_filename);

		int predict_beat_one_vs_one_SVM(svm_node* feature);
  
		void compute_RR_intervals(std::vector<int> poses, std::vector<float> &pre_R,
								  std::vector<float> &post_R, std::vector<float> &local_R,
								  std::vector<float> &global_R);  

							//(std::vector<float>beat, 
		svm_node *compute_feature(float pre_R, float post_R, float local_R, float global_R);

		void resample_freq(std::vector<float> &ecg, float fs_or, float fs);

	private:
		std::vector<svm_model*> models;
		svm_model *model;

		int n_classes;
		std::string _svm_model_name;
		int _w_l, _w_r;
		std::vector<int> r_peaks;
		std::vector<float> ecg;
		bool _use_wavelets, _use_RR_intervals;
};

#endif
