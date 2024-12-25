package com.myapp.controller;

import com.myapp.model.Product;
import com.myapp.service.ProductService;

public class ProductController {

    private ProductService productService;

    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    public void createProduct(int id, String name, double price) {
        Product product = new Product(id, name, price);
        productService.addProduct(product);
    }

    public void displayProduct(int id) {
        Product product = productService.getProductById(id);
        System.out.println(product);
    }
}
