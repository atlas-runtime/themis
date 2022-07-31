function change (coins, amount) {
  const combinations = new Array(amount + 1).fill(0)
  combinations[0] = 1

  for (let i = 0; i < coins.length; i++) {
    const coin = coins[i]

    for (let j = coin; j < amount + 1; j++) {
      combinations[j] += combinations[j - coin]
    }
  }
  return combinations[amount]
}

function minimumCoins (coins, amount) {
  // minimumCoins[i] will store the minimum coins needed for amount i
  const minimumCoins = new Array(amount + 1).fill(0)

  minimumCoins[0] = 0

  for (let i = 1; i < amount + 1; i++) {
    minimumCoins[i] = Number.MAX_SAFE_INTEGER
  }
  for (let i = 1; i < amount + 1; i++) {
    for (let j = 0; j < coins.length; j++) {
      const coin = coins[j]
      if (coin <= i) {
        const subRes = minimumCoins[i - coin]
        if (subRes !== Number.MAX_SAFE_INTEGER && subRes + 1 < minimumCoins[i]) {
          minimumCoins[i] = subRes + 1
        }
      }
    }
  }
  return minimumCoins[amount]
}

export function CoinChange_bench (size) {
  const coins = [1,2,3,4,5]
  change(coins, size)
   minimumCoins(coins, size)
   return "bench_done"
}
// CoinChange_bench(1000000)