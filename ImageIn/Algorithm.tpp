
    
template <class I>
I* Algorithm_t<I,1>::operator() (const imagein::Image_t<typename I::depth_t>* img) const { 
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    return this->algorithm(imgs);
}

template <class I>
I* Algorithm_t<I,2>::operator() (const imagein::Image_t<typename I::depth_t>* img, const imagein::Image_t<typename I::depth_t>* img2) const { 
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    return this->algorithm(imgs);
}

template <class I>
I* Algorithm_t<I,3>::operator() (const imagein::Image_t<typename I::depth_t>* img, const imagein::Image_t<typename I::depth_t>* img2, const imagein::Image_t<typename I::depth_t>* img3) const { 
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    imgs.push_back(img3);
    return this->algorithm(imgs);
}
