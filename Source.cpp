#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>


using namespace std;
int main(int argc, char*argv[])
{
    
    /*
     CMatrix z;
     CMatrix x("[6 5 4;3 2 1]");
     CMatrix y("[1 2 3;4 5 6]");
     z = "[0 2 4;4 5 6]";
     cout<< "z =\n\n" << z.getString() << "\nx =\n\n" << x.getString() << "\ny =\n\n" << y.getString();
    	 z= y+x;
    	cout<< "\nz= x+y\n\n" << z.getString();

    //////////////////////////////////////////////////////////////////
    CMatrix f(x);

    	 z=++f;
    	 cout<<"\nf=x\nz = ++f\nz=\n\n"<<z.getString()<<endl<<"f=\n\n"<<f.getString() ;

    //////////////////////////////////////////////////////////////////
    	 CMatrix a(x);
    	 z =a++;
    	 cout<<"\na=x\nz = a++\nz=\n\n"<<z.getString()<<endl<<"a=\n\n"<<a.getString()<< endl ;

    //////////////////////////////////////////////////////////////////
    	 CMatrix b(x);
    	 z =b--;
    	 cout<<"\nb=x\nz = b--\nz=\n\n"<<z.getString()<<endl<<"b=\n\n"<<b.getString()<< endl ;

    //////////////////////////////////////////////////////////////////
    	 CMatrix c(x);
    	 z =--c;
    	 cout<<"\nc=x\nz = --c\nz=\n\n"<<z.getString()<<endl<<"c=\n\n"<<c.getString()<< endl ;

    //////////////////////////////////////////////////////////////////

    	 z = x.getCofactor(1,1);
    	 cout<< "z= x.getCofactor(1,1)\nz=\n\n" << z.getString()<<endl<<"x=\n\n"<<x.getString() ;
    //////////////////////////////////////////////////////////////////
    	z = x;
    	z+=y;
    	cout<<"\nz= x\nz+=y\n\n"<<z.getString() ;
    //////////////////////////////////////////////////////////////////
    	z = -x;
    	cout<<"\nz= -x\n\n"<<z.getString() ;
    //////////////////////////////////////////////////////////////////
    	z/=2;
    	cout<< "\nz/=2\n\n" << z.getString() ;
    //////////////////////////////////////////////////////////////////
    	z = x;
    	z.reset();
    	cout<<z.getString() ;
    */


    /*
     CMatrix z("[25.229 20.511 28.959 5.16 3.935 19.835 11.729 32.51 11.864 2.903 30.758 6.025 29.791 10.128 0.21 27.832 4.464 15.296 15.965 4.362 11.235 31.596 25.218 19.035 8.433 0.639 16.086 29.694 11.892 26.615 23.722 18.187 ;27.118 26.847 19.505 31.994 10.445 16.253 28.39 0.113 15.853 31.436 16.68 8.283 12.383 27.181 26.407 31.034 20.329 29.017 0.26 2.238 18.381 22.682 2.612 8.086 7.758 27.963 18.47 9.606 13.169 1.596 3.109 25.53 ;13.441 16.715 19.583 18.778 7.637 3.056 22.759 24.158 12.886 19.72 11.8 22.692 3.131 17.012 11.451 1.855 11.031 26.386 14.219 2.067 8.982 29.932 31.927 31.647 20.867 22.448 28.295 11.033 14.99 9.057 12.099 21.696 ;29.773 25.419 29.777 4.718 17.152 21.82 9.373 3.692 19.097 25.841 13.886 31.371 31.1 31.695 3.926 32.112 4.227 30.932 28.217 2.608 27.717 25.804 7.378 22.045 29.592 14.024 29.507 24.799 20.308 15.564 28.108 17.094 ;20.314 31.944 23.022 13.662 8.405 8.649 24.272 2.628 14.784 18.801 25.825 1.081 7.593 17.829 8.383 18.037 24.5 9.861 17.752 20.029 1.506 8.353 8.527 10.936 12.691 9.065 11.169 26.367 12.618 13.286 17.288 23.155 ;24.497 24.488 10.143 21.331 29.661 23.552 26.695 20.366 9.938 9.583 22.858 14.293 21.066 13.149 18.111 20.725 27.826 5.134 28.974 22.372 1.654 1.235 5.364 31.001 11.39 23.165 0.232 8.609 21.497 19.991 0.062 19.568 ;13.145 0.469 7.084 20.853 11.422 21.063 30.156 24.561 11.48 18.386 18.114 7.048 9.447 15.457 15.134 3.993 32.646 2.392 14.852 27.851 14.472 20.938 22.154 17.64 31.072 15.595 28.769 14.575 24.295 13.512 18.36 19.812 ;19.546 32.053 2.141 22.763 28.578 14.087 4.133 16.661 23.257 9.092 29.839 31.098 22.281 15.384 2.98 30.984 21.559 29.258 31.777 6.554 6.816 11.245 6.36 5.58 8.514 20.379 2.9 6.414 11.678 30.047 4.54 5.624 ;8.381 4.018 21.497 22.238 5.489 8.361 5.147 31.907 13.277 20.332 15.865 24.53 24.119 29.162 6.68 2.026 6.861 24.267 10.191 11.514 24.39 7.078 25.256 30.574 8.491 15.221 30.472 29.225 20.39 0.326 10.771 25.3 ;6.793 6.963 30.922 31.861 10.897 2.451 12.918 8.259 12.013 1.65 4.682 8.377 25.594 0.319 7.236 15.081 30.545 0.709 16.724 14.867 27.907 3.421 3.776 31.094 27.171 19.809 27.847 14.438 2.181 11.747 12.421 29.855 ;6.086 9.631 1.302 16.089 28.556 20.527 28.67 15.772 14.095 10.11 29.896 21.078 17.881 29.055 7.15 5.291 0.458 13.855 24.825 6.156 24.158 20.856 19.433 12.171 24.883 30.279 14.807 9.197 20.421 13.472 6.361 4.097 ;27.26 22.752 6.95 22.321 22.762 14.052 9.595 27.223 11.085 13.688 31.933 20.178 5.468 11.794 30.431 7.128 17.984 29.889 13.062 25.101 0.48 7.264 7.403 12.629 24.417 19.215 16.257 12.519 20.717 13.028 10.969 32.164 ;22.708 0.733 28.994 17.062 3.889 25.625 32.692 16.411 24.239 22.344 21.871 13.396 6.155 1.633 24.287 23.321 17.595 24.211 30.659 30.528 23.055 1.661 22.67 6.782 12.727 1.185 29.453 8.06 27.526 10.774 0.587 2.605 ;7.286 5.502 20.914 16.992 28.395 25.144 32.626 23.697 6.204 22.487 15.911 25.861 18.287 11.73 22.966 24.854 28.996 14.204 0.887 31.435 7.542 3.127 10.65 2.731 6.461 32.741 24.003 29.651 13.079 32.672 3.832 1.607 ;25.544 9.899 6.845 23.43 2.207 8.104 31.101 24.929 4.86 9.739 2.604 1.804 20.751 15.31 16.683 16.502 13.282 26.471 15.98 21.462 13.978 3.575 3.798 9.606 19.194 15.812 7.403 30.229 28.456 31.977 5.288 18.072 ;20.66 28.748 16.044 22.336 8.406 28.369 5.789 29.746 32.247 21.709 8.392 1.17 5.747 11.198 17.159 4.065 26.782 31.289 9.448 11.658 17.413 20.515 23.307 4.791 28.662 25.38 25.036 12.905 6.978 20.313 11.042 9.16 ;31.041 20.553 17.351 17.08 12.311 1.563 21.402 16.044 31.798 6.918 32.065 3.007 11.556 23.816 24.85 27.137 24.447 8.155 18.228 30.478 6.206 31.525 13.569 32.23 9.529 14.575 29.103 30.968 26.348 2.136 15.92 31.36 ;26.487 18.57 17.494 28.435 25.322 32.75 0.315 28.28 9.408 21.404 12 3.77 24.233 4.886 28.948 28.027 23.693 11.317 18.84 25.483 14.797 7.011 6.016 5.818 31.692 11.275 9.692 24.042 13.742 7.502 3.48 11.112 ;6.495 32.504 28.321 29.052 6.615 23.218 17.481 13.63 0.669 32.121 22.765 17.324 10.378 30.03 7.381 15.61 6.096 5.935 25.691 27.177 25.403 8.519 20.816 4.315 30.902 19.81 27.547 14.694 7.952 26.531 11.555 6.951 ;0.256 15.737 1.264 8.985 26.983 30.927 5.517 18.597 5.334 15.235 12.976 9.404 15.44 3.866 25.116 32.548 15.697 31.922 25.543 17.935 0.782 24.887 1.336 9.202 5.375 20.954 17.46 10.132 28.315 9.407 1.177 12.902 ;1.123 29.174 23.946 8.466 6.689 8.365 16.844 25.174 20.082 21.668 1.904 28.691 32.642 20.449 4.787 24.225 27.927 7.332 10.274 30.31 15.313 5.021 10.754 2.983 15.792 4.701 17.646 2.205 9.174 30.219 20.418 24.012 ;32.142 11.864 25.272 19.6 10.382 31.924 27.089 16.377 5.753 13.251 13.943 10.2 2.984 2.826 21.6 2.586 15.146 23.279 9.653 15.957 25.609 21.728 2.676 1.953 21.455 3.026 5.907 0.169 29.257 24.813 7.782 3.586 ;14.987 10.373 4.802 19.131 17.716 6.989 0.611 9.013 18.42 26.567 13.067 4.66 11.851 30.719 8.428 13.367 12.179 16.249 25.8 9.477 1.6 9.576 17.751 23.433 11.367 24.352 30.697 30.687 16.765 20.174 21.58 14.255 ;32.098 14.951 32.752 1.21 21.661 28.382 21.577 20.914 12.778 9.114 1.141 14.671 26.866 12.839 17.951 5.023 18.009 30.252 0.419 30.11 24.829 27.037 19.826 20.23 4.221 20.785 14.521 6.76 11.513 3.351 10.557 21.372 ;31.769 25.061 20.617 10.166 28.497 19.921 31.82 5.401 5.987 15.907 17.917 27.472 28.965 14.57 26.048 25.339 28.548 20.206 11.405 16.199 26.313 27.111 27.023 11.713 15.643 19.18 16.074 22.636 1.093 19.758 10.497 24.08 ;24.762 16.614 16.087 9.43 25.046 29.324 27.444 15.122 12.135 12.874 9.962 14.944 12.396 28.592 30.105 24.818 3.869 15.785 10.704 21.8 15.915 21.166 13.428 18.273 25.416 22.841 0.87 26.13 19.178 9.341 13.152 22.549 ;18.764 7.508 6.432 12.611 11.446 31.609 26.057 5.444 9.471 7.927 27.27 31.91 17.488 7.649 16.24 20.525 32.042 23.108 20.914 20.074 16.811 13.402 7.402 28.559 10.253 11.52 5.075 15.234 14.447 3.178 31.778 17.968 ;18.392 24.854 16.813 17.956 1.145 27.39 1.234 31.064 5.938 18.194 26.647 19.531 32.344 28.389 24.846 30.547 1.462 24.743 4.22 1.589 32.721 0.851 26.041 32.243 9.329 6.953 4.442 5.349 14.428 25.183 2.83 12.555 ;25.189 6.676 11.974 8.354 20.901 10.117 13.593 16.629 6.409 4.483 2.79 1.91 25.613 29.221 19.515 8.461 26.822 12.474 26.229 7.088 15.142 6.145 9.641 20.02 25.98 7.325 12.611 29.283 27.194 26.563 15.341 9.55 ;4.859 31.286 27.315 16.869 12.484 31.605 14.18 18.884 12.682 2.354 21.051 20.56 12.021 6.919 18.11 7.171 23.14 20.069 26.599 29.188 27.185 11.981 18.306 16.379 27.702 20.034 15.574 6.179 8.592 16.894 16.007 13.217 ;18.338 22.372 5.051 28.436 29.277 5.43 8.316 30.061 23.487 23.816 20.83 3.329 19.61 16.628 27.233 15.068 0.663 24.976 15.64 12.376 14.202 26.653 2.571 14.063 11.688 28.929 4.443 3.662 26.086 31.352 5.796 28.842 ;25.187 11.142 23.591 12.631 6.905 1.84 22.825 10.647 1.712 24.555 12.182 26.544 24.196 8.021 9.45 21.569 32.104 13.859 8.785 16.853 0.394 18.522 0.013 6.841 4.825 27.075 8.217 8.459 29.381 32.408 7.18 29.972 ;]");

     CMatrix y("[9.922 17.167 29.964 24.53 7.42 11.772 7.861 10.707 22.345 28.256 26.335 12.166 15.575 9.733 8.775 1.164 7.505 1.591 7.19 27.189 3.157 3.435 27.898 6.726 4.391 18.469 18.555 12.026 32.423 6.424 13.453 19.526 ;1.92 19.598 24.417 28.257 25.251 31.498 1.921 0.388 5.108 32.556 10.78 9.967 11.586 0.726 27.55 19.244 7.037 26.509 28.292 29.079 21.539 3.618 3.183 22.814 30.46 16.785 9.591 24.134 14.343 18.729 31.169 15.982 ;9.652 26.093 16.724 8.28 8.019 16.187 30.248 1.509 4.045 0.683 1.152 2.848 16.53 15.162 21.882 5.758 22.738 9.128 26.597 24.165 23.792 30.75 27.474 26.602 16.948 2.836 4.462 25.311 27.328 8.562 2.447 1.805 ;7.621 23.029 23.18 22.206 20.47 9.173 3.794 27.263 20.541 2.213 26.292 10.787 11.437 19.834 1.283 5.899 25.529 12.111 18.911 2.981 13.731 16.04 20.428 5.171 10.807 7.798 16.137 17.614 7.864 10.811 27.421 12.458 ;28.699 18.286 28.338 26.267 5.491 26.145 14.758 5.848 16.045 29.921 17.76 17.92 19.325 19.422 25.44 12.634 11.928 21.324 23.066 18.529 4.388 26.888 17.413 24.448 19.052 18.815 25.839 0.026 32.729 32.716 27.027 31.181 ;0.286 8.48 17.773 6.392 13.49 22.375 8.909 9.85 10.371 32.552 6.443 5.309 6.889 23.725 7.61 32.244 4.056 11.365 25.151 22.432 18.011 4.742 5.668 32.601 8.765 11.766 15.816 1.227 24.073 21.1 5.146 21.759 ;6.454 11.731 10.854 10.972 5.787 23.791 14.959 26.861 16.169 13.122 24.253 16.484 15.576 14.897 9.528 18.783 16.866 11.107 12.278 28.779 20.528 27.242 22.61 23.878 5.393 16.805 2.11 14.058 11.57 26.212 15.834 26.822 ;25.803 2.126 27.973 19.791 18.454 28.672 13.49 25.015 6.149 28.919 5.823 26.364 30.516 12.976 12.035 5.157 25.373 5.389 5.35 15.817 19.851 13.307 24.758 5.84 27.217 20.05 1.783 28.285 1.339 5.117 32.25 4.013 ;29.765 8.026 25.009 9.561 31.243 7.651 2.497 18.53 11.393 27.663 17.881 6.798 13.284 10.355 13.378 4.813 30.192 0.557 26.296 24.258 0.34 18.05 18.809 32.126 19.811 29.126 0.155 30.607 8.716 18.3 12.194 22.585 ;15.372 13.759 24.402 19.459 0.354 2.017 30.146 2.166 23.043 11.345 29.874 24.865 0.208 4.546 29.214 11.744 24.773 24.457 32.532 26.206 21.107 3.399 28.866 5.849 19.888 7.625 16.339 4.645 25.485 0.3 29.18 1.268 ;5.256 25.157 16.849 20.052 22.275 25.408 30.942 16.761 25.077 3.462 12.275 13.501 4.064 30.949 27.071 0.485 28.163 28.139 15.264 23.462 19.408 1.938 30.906 7.272 24.224 6.179 4.935 29.257 19.878 21.844 10.285 3.173 ;14.881 4.019 26.838 11.605 6.102 31.048 22.332 18.165 27.07 16.246 2.115 0.874 14.076 31.779 24.652 24.42 19.473 16.921 32.263 14.753 7.251 18.603 18.312 31.667 22.428 31.387 19.87 16.386 2.111 27.707 31.072 6.42 ;19.776 31.955 14.344 24.076 1.22 10.051 6.405 8.305 31.43 17.897 4.683 12.081 28.684 19.909 24.302 19.174 3.417 17.627 11.247 28.503 5.861 30.681 1.878 22.082 29.706 13.05 17.792 5.977 24.384 0.554 20.667 2.442 ;21.067 15.467 5.904 18.819 0.691 24.183 2.656 2.422 0.629 30.887 26.291 3.609 22.776 13.331 13.004 31.986 10.306 13.051 12.033 24.529 12.908 20.582 9.801 0.414 21.331 0.776 21.911 2.132 17.041 26.473 23.91 28.75 ;12.716 13.636 29.077 19.65 6.796 9.261 15.222 29.067 21.043 0.887 8.738 27.179 13.224 2.389 27.919 25.104 30.516 7.487 29.924 25.11 2.513 8.6 22.155 1.87 30.944 0.141 23.688 5.886 17.946 0.064 4.746 5.096 ;14.281 8.742 14.144 14.543 31.032 4.525 0.11 31.8 8.04 26.147 25.92 0.366 26.116 15.315 25.31 6.856 14.487 26.737 28.48 16.686 23.549 20.152 3.652 9.434 19.48 5.457 15.614 15.196 8.644 17.655 10.063 28.385 ;5.388 4.569 23.481 21.172 28.574 21.567 29.041 0.261 0.892 29.809 21.686 1.514 31.221 19.925 11.618 31.651 3.796 19.799 5.055 15.394 3.031 20.237 1.947 19.403 6.242 32.539 23.967 24.952 12.661 16.853 5.852 12.224 ;24.028 26.404 22.183 21.369 29.349 11.563 27.303 2.939 31.703 22.058 6.444 7.591 7.521 21.922 10.69 3.368 0.081 22.714 23.559 1.529 8.262 11.745 16.569 8.615 3.368 20.405 10.515 26.969 29.974 5.923 8.282 14.605 ;2.72 22.736 9.139 26.66 6.967 29.112 3.127 23.329 27.105 1.814 24.393 25.262 8.754 32.131 31.015 3.04 30.583 27.489 17.856 17.851 17.46 2.682 31.686 32.761 15.825 27.877 3.587 9.991 4.24 31.018 18.16 8.529 ;30.658 29.093 17.028 12.735 9.787 2.864 14.922 25.471 4.867 22.268 22.454 25.35 32.334 0.96 0.185 26.705 17.07 14.87 21.139 5.745 18.056 6.177 16.105 29.766 8.645 4.212 32.535 25.227 19.401 12.335 20.935 13.074 ;26.025 4.203 14.019 17.745 29.848 30.425 7.431 19.486 8.355 27.045 14.107 8.375 19.359 15.009 27.039 18.181 5.215 19.871 2.087 1.826 6.698 7.71 21.578 16.408 5.227 18.474 29.43 22.508 4.779 6.269 19.462 27.867 ;30.909 26.602 2.071 11.235 2.872 17.916 8.343 28.805 8.235 14.042 13.854 4.554 18.443 2.157 8.45 0.132 0.752 0.709 28.71 6.87 22.017 30.649 18.962 22.774 21.805 30.158 25.673 14.13 29.981 8.795 1.238 0.305 ;14.694 32.49 16.937 25.212 4.866 7.648 29.985 24.636 0.769 2.657 4.458 8.262 21.884 26.478 22.537 8.532 2.251 2.64 6.197 18.581 13.559 5.178 29.289 26.729 1.906 20.266 20.919 9.317 9.99 21.008 3.935 22.174 ;5.132 12.338 29.856 23.076 22.75 14.287 3.79 24.268 7.823 1.026 2.469 10.803 31.193 26.09 0.989 27.135 1.11 26.888 4.606 31.592 5.619 30.44 25.462 19.448 12.963 24.068 15.849 14.222 0.08 16.357 17.096 1.961 ;22.807 10.891 13.093 30.691 19.892 24.847 9.67 25.532 11.323 6.023 25.464 0.409 24.33 9.77 23.973 20.237 14.331 30.645 29.481 4.694 31.71 14.093 30.562 5.419 16.934 0.037 12.166 31.925 31.97 6.178 14.906 25.307 ;15.599 28.861 5.472 5.314 1.644 31.465 13.872 6.804 18.799 3.254 26.506 27.777 21.238 24.182 25.226 30.98 18.977 25.374 21.854 24.68 3.486 32.751 19.54 2.442 1.38 26.453 12.599 29.664 15.524 6.927 21.724 27.322 ;22.524 22.928 14.072 32.2 15.343 31.397 0.052 25.309 30.61 32.601 25.22 9.458 18.311 22.806 21.428 17.518 17.711 11.276 22.084 11.429 5.66 4.31 17.525 8.862 12.229 6.491 20.9 4.377 0.894 7.411 13.783 21.968 ;9.895 4.044 14.23 29.694 19.235 27.019 2.044 20.51 7.18 24.374 9.485 22.773 21.156 29.777 13.898 16.85 6.031 10.055 6.019 12.821 1.088 15.628 1.517 3.566 22.706 28.673 9.076 15.463 14.68 1.56 17.49 3.749 ;2.39 4.664 15.073 11.37 13.553 25.827 5.549 10.719 0.068 28.694 0.974 10.897 11.829 8.816 21.365 13.753 5.032 32.151 16.068 8.128 27.379 27.608 31.459 11.522 31.633 6.413 15.696 20.947 27.162 21.188 11.126 13.247 ;17.522 13.213 26.754 20.502 7.745 7.668 13.682 27.561 20.9 18.88 22.382 12.238 14.371 27.067 14.428 6.314 28.642 11.204 30.127 6.319 0.283 6.273 20.863 5.475 30.667 5.704 14.815 8.547 17.836 4.928 23.147 6.056 ;0.1 6.851 27.68 31.754 20.476 23.047 14.193 17.666 8.595 22.526 31.894 29.364 29.268 25.722 13.864 5.933 18.085 0.661 27.115 13.289 8.609 21.072 31.723 4.248 4.297 15.738 14.282 28.449 8.182 27.604 1.112 16.616 ;18.835 17.01 30.052 16.717 14.088 29.284 12.242 6.517 25.977 23.19 21.486 29.004 0.689 16.629 25.088 4.554 5.721 9.939 19.745 31.862 19.31 15.501 12.364 7.209 28.146 14.443 22.968 29.461 28.897 5.319 8.293 27.141 ;]");
    CMatrix x("[1 2 2 7; 2 0 -1 20; -2 1 3 10; 10 90 8 -2]");
     x = y.getTranspose();
     CMatrix f(32,32);
      f = x+z;
      f = 1 / z;
        cout<<f.getDeterminant()<<endl;
        cout<<y.getDeterminant()<<endl;
        cout<<z.getDeterminant()<<endl;
    */
    return 0;
}
