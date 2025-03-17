


// Service layer
package com.supermarket.api.service;

@Service
public class SupermarketService {
	private final ProductRepository productRepository;
	private final StoreRepository storeRepository;
	private final PriceRepository priceRepository;

	@Autowired
	public SupermarketService(ProductRepository productRepository,
							  StoreRepository storeRepository,
							  PriceRepository priceRepository) {
		this.productRepository = productRepository;
		this.storeRepository = storeRepository;
		this.priceRepository = priceRepository;
	}

	public List<Product> getAllProducts() {
		return productRepository.findAll();
	}

	public Product getProduct(String id) {
		return productRepository.findById(id)
				.orElseThrow(() -> new ResourceNotFoundException("Product not found"));
	}

	public List<Store> getAllStores() {
		return storeRepository.findAll();
	}

	public List<Price> getPricesForProduct(String productId) {
		return priceRepository.findByProductId(productId);
	}

	public List<Price> getPricesForStore(String storeId) {
		return priceRepository.findByStoreId(storeId);
	}
}

// Controller layer
package com.supermarket.api.controller;

@RestController
@RequestMapping("/api")
public class SupermarketController {
	private final SupermarketService service;

	@Autowired
	public SupermarketController(SupermarketService service) {
		this.service = service;
	}

	@GetMapping("/products")
	public ResponseEntity<List<Product>> getAllProducts() {
		return ResponseEntity.ok(service.getAllProducts());
	}

	@GetMapping("/products/{id}")
	public ResponseEntity<Product> getProduct(@PathVariable String id) {
		return ResponseEntity.ok(service.getProduct(id));
	}

	@GetMapping("/stores")
	public ResponseEntity<List<Store>> getAllStores() {
		return ResponseEntity.ok(service.getAllStores());
	}

	@GetMapping("/prices/product/{productId}")
	public ResponseEntity<List<Price>> getPricesForProduct(@PathVariable String productId) {
		return ResponseEntity.ok(service.getPricesForProduct(productId));
	}

	@GetMapping("/prices/store/{storeId}")
	public ResponseEntity<List<Price>> getPricesForStore(@PathVariable String storeId) {
		return ResponseEntity.ok(service.getPricesForStore(storeId));
	}
}

// Main Application class
package com.supermarket.api;

@SpringBootApplication
public class SupermarketApiApplication {
	public static void main(String[] args) {
		SpringApplication.run(SupermarketApiApplication.class, args);
	}
}