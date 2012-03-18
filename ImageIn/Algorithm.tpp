
    
template <typename D, template <typename D> class I>
I<D>* Algorithm_t<D,I,1>::operator() (const imagein::Image_t<D>* img) const { 
    std::vector<const imagein::Image_t<D>*> imgs;
    imgs.push_back(img);
    return this->algorithm(imgs);
}

template <typename D, template <typename D> class I>
I<D>* Algorithm_t<D,I,2>::operator() (const imagein::Image_t<D>* img, const imagein::Image_t<D>* img2) const { 
    std::vector<const imagein::Image_t<D>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    return this->algorithm(imgs);
}

template <typename D, template <typename D> class I>
inline I<D>* Algorithm_t<D,I,3>::operator() (const imagein::Image_t<D>* img, const imagein::Image_t<D>* img2, const imagein::Image_t<D>* img3) const { 
    std::vector<const imagein::Image_t<D>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    imgs.push_back(img3);
    return this->algorithm(imgs);
}
