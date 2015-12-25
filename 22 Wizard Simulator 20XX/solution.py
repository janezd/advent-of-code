# I hated this one -- mostly about getting the instructions right.

import itertools

# (cost, time, (damage, healing, armor, mana))
weapons = [(53, 0, (4, 0, 0, 0)),  # Magic missile
           (73, 0, (2, 2, 0, 0)),  # Drain
           (113, 6, (0, 0, 7, 0)),  # Shield
           (173, 6, (3, 0, 0, 0)),  # Poison
           (229, 5, (0, 0, 0, 101))  # Recharge
           ]

costs = [53, 73, 113, 173, 229]

log = False

def game(moves):
    def apply_effects():
        nonlocal shield, poison, recharge
        nonlocal b_p, m_m, m_a
        m_a = 7 * (shield > 0)
        shield -= 1

        b_p -= 3 * (poison > 0)
        poison -= 1

        m_m += 101 * (recharge > 0)
        recharge -= 1

    b_p, b_d = b_points, b_damage
    m_p, m_m, m_a = m_points, m_mana, m_armour
    shield = poison = recharge = 0

    for move in moves:
        # player's turn
        if log:
            print("Player")
            print(m_p, m_a, m_m)
            print(b_p)
            print()
        m_p -= 1
        if m_p <= 0:
            return False
        apply_effects()
        if b_p <= 0:
            return True
        cost = costs[move]
        if cost > m_m:
            return False
        m_m -= cost
        if move == 0:
            b_p -= 4
        if move == 1:
            b_p -= 2
            m_p += 2
        if b_p <= 0:
            return True
        if move == 2:
            if shield > 0:
                return False
            shield = 6
        if move == 3:
            if poison > 0:
                return False
            poison = 6
        if move == 4:
            if recharge > 0:
                return False
            recharge = 5

        # boss' turn
        if log:
            print("Boss")
            print(m_p, m_a, m_m)
            print(b_p)
            print()
        apply_effects()
        if b_p <= 0:
            return True
        if b_d > m_a:
            m_p -= max(1, b_d - m_a)
        if m_p <= 0:
            return False
    return False


def try_all():
    best = 9999999
    i = 9
    for moves in itertools.product(range(len(weapons)), repeat=i):
        cost = sum(costs[i] for i in moves)
        if cost < best and game(moves):
            best = cost
            print(cost)
    return best

b_points, b_damage = 58, 9
m_points, m_mana, m_armour = 50, 500, 0

print(try_all())
