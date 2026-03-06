const express = require('express');
const router = express.Router();
const carController = require('../controllers/carController');

router.get('/', carController.getAllCars);
router.get('/:id', carController.getOneCar);
router.post('/', carController.addCar);
router.delete('/:id', carController.deleteCar);
router.put('/:id', carController.updateCar);

module.exports = router;