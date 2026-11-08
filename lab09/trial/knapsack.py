def knapsack(weights, values, capacity):
    n = len(weights)

    # Number of columns in the conceptual DP table.
    width = capacity + 1

    # Flatten the (n + 1) x (capacity + 1) DP table
    # into a single 1D list.
    dp = [0] * ((n + 1) * width)

    # Build the DP table, one item at a time.
    for i in range(1, n + 1):
        weight = weights[i - 1]
        value = values[i - 1]

        # Calculate the starting positions of the current
        # and previous rows in the flattened list.
        current = i * width
        previous = (i - 1) * width

        for w in range(capacity + 1):

            # Choice 1: Do not take the current item.
            dp[current + w] = dp[previous + w]

            # Choice 2: Take the current item, if it fits.
            if weight <= w:
                take = value + dp[previous + w - weight]

                dp[current + w] = max(
                    dp[current + w],
                    take
                )

    # The bottom-right cell contains the optimal value.
    max_value = dp[n * width + capacity]

    # Reconstruct the selected items.
    selected = []
    w = capacity

    for i in range(n, 0, -1):
        current = i * width
        previous = (i - 1) * width

        # If the current and previous rows differ,
        # the current item was included in the solution.
        if dp[current + w] != dp[previous + w]:
            selected.append(i - 1)
            w -= weights[i - 1]

    selected.reverse()

    return max_value, selected


# Example
weights = [12, 1, 4, 1, 2]
values = [4, 2, 10, 1, 2]
capacity = 15

max_value, selected = knapsack(weights, values, capacity)

print("Maximum value:", max_value)
print("Selected items:", [i + 1 for i in selected])
print("Total weight:", sum(weights[i] for i in selected))