// utils/Cart.js

export class Cart {
  constructor() {
    this.items = []
  }

  addItem(item) {
    this.items = [...this.items, item]
  }

  removeItem(id) {
    this.items = this.items.filter(i => i.id !== id)
  }

  getTotal() {
    return this.items.reduce((sum, i) => sum + i.price, 0)
  }
}

//
// components/CartPage.jsx

import { useState } from 'react'
import { Cart } from '../utils/Cart'

function CartPage() {
  const [cart] = useState(() => new Cart())
  const [items, setItems] = useState([])

  const handleAdd = (item) => {
    cart.addItem(item)
    setItems([...cart.items]) // sync state with class
  }

  return (
    <div>
      {items.map(i => <p key={i.id}>{i.name}</p>)}
    </div>
  )
}
