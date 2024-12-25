package com.myapp.service;

import com.myapp.model.Product;
import com.myapp.dao.ProductDao;

public class ProductService {

    private ProductDao productDao;

    public ProductService(ProductDao productDao) {
        this.productDao = productDao;
    }

    public Product getProductById(int id) {
        return productDao.findById(id);
    }

    public void addProduct(Product product) {
        productDao.save(product);
    }
}
