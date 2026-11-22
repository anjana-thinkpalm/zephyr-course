/*
 * Ring Buffer Module - Homework Test Skeleton
 *
 * test_fresh_state is provided as a worked example. The remaining 7 ZTEST
 * bodies are implemented according to TEST_SPEC.md (8 tests in total).
 *
 * Run:
 *   west twister -T tests/ring_buf -p native_sim
 */

#include <zephyr/ztest.h>
#include <errno.h>

#include "ring_buf.h"

/*
 * Shared before hook: every suite reinitialises the ring buffer with a
 * capacity of 4 so tests start from a clean, known state. Capacity 4 is
 * enough to exercise FIFO order (push 1, 2, 3) and overflow (full at 4).
 */
static void before(void *f)
{
	ARG_UNUSED(f);
	rb_init(4);
}

/*
 * ============================================================================
 * Test Suite: ring_buf_init
 *
 * Initial state and re-initialization behaviour.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_init, NULL, NULL, before, NULL, NULL);

/* PROVIDED — study this test before writing the rest. */
ZTEST(ring_buf_init, test_fresh_state)
{
	zassert_true(rb_is_empty(), "Fresh buffer must be empty");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0");
}

ZTEST(ring_buf_init, test_reinit_clears_state)
{
	int ret;

	ret = rb_push(99);
	zassert_equal(ret, 0, "Push must succeed");
	zassert_equal(rb_count(), 1, "Count must be 1 after push");

	/* Re-initialising must discard the previous contents. */
	ret = rb_init(4);
	zassert_equal(ret, 0, "rb_init(4) must succeed");

	zassert_true(rb_is_empty(), "Buffer must be empty after reinit");
	zassert_equal(rb_count(), 0, "Count must be 0 after reinit");
}

/*
 * ============================================================================
 * Test Suite: ring_buf_push_pop
 *
 * Single push/pop round-trip, FIFO order, full error path.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_push_pop, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_push_pop, test_single_push_pop)
{
	int v = 0;
	int ret;

	ret = rb_push(42);
	zassert_equal(ret, 0, "Push must succeed");

	ret = rb_pop(&v);
	zassert_equal(ret, 0, "Pop must succeed");
	zassert_equal(v, 42, "Popped value must be 42, got %d", v);

	zassert_true(rb_is_empty(), "Buffer must be empty after the pop");
}

ZTEST(ring_buf_push_pop, test_fifo_order)
{
	int v = 0;
	int ret;

	zassert_equal(rb_push(1), 0, "Push 1 must succeed");
	zassert_equal(rb_push(2), 0, "Push 2 must succeed");
	zassert_equal(rb_push(3), 0, "Push 3 must succeed");

	ret = rb_pop(&v);
	zassert_equal(ret, 0, "First pop must succeed");
	zassert_equal(v, 1, "First pop must yield 1, got %d", v);

	ret = rb_pop(&v);
	zassert_equal(ret, 0, "Second pop must succeed");
	zassert_equal(v, 2, "Second pop must yield 2, got %d", v);

	ret = rb_pop(&v);
	zassert_equal(ret, 0, "Third pop must succeed");
	zassert_equal(v, 3, "Third pop must yield 3, got %d", v);

	zassert_true(rb_is_empty(), "Buffer must be empty after three pops");
}

ZTEST(ring_buf_push_pop, test_push_full_returns_enospc)
{
	int ret;

	for (int i = 1; i <= 4; i++) {
		ret = rb_push(i);
		zassert_equal(ret, 0, "Push %d must succeed", i);
	}
	zassert_true(rb_is_full(), "Buffer must be full after 4 pushes");

	ret = rb_push(99);
	zassert_equal(ret, -ENOSPC, "Push on a full buffer must return -ENOSPC, got %d", ret);

	zassert_equal(rb_count(), 4, "Rejected push must not consume a slot");
}

/*
 * ============================================================================
 * Test Suite: ring_buf_boundaries
 *
 * Peek semantics and NULL-pointer boundary conditions.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_boundaries, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_boundaries, test_peek_does_not_consume)
{
	int v = 0;
	int ret;

	zassert_equal(rb_push(7), 0, "Push must succeed");

	ret = rb_peek(&v);
	zassert_equal(ret, 0, "First peek must succeed");
	zassert_equal(v, 7, "First peek must yield 7, got %d", v);

	v = 0;
	ret = rb_peek(&v);
	zassert_equal(ret, 0, "Second peek must succeed");
	zassert_equal(v, 7, "Second peek must yield 7, got %d", v);

	zassert_equal(rb_count(), 1, "Peek must not consume the element");
}

ZTEST(ring_buf_boundaries, test_pop_null_returns_einval)
{
	int ret = rb_pop(NULL);

	zassert_equal(ret, -EINVAL, "rb_pop(NULL) must return -EINVAL, got %d", ret);
}

ZTEST(ring_buf_boundaries, test_is_full_after_fill)
{
	for (int i = 1; i <= 4; i++) {
		zassert_equal(rb_push(i), 0, "Push %d must succeed", i);
	}

	zassert_true(rb_is_full(), "Buffer must be full after filling to capacity");
	zassert_equal(rb_count(), 4, "Count must equal the capacity of 4");
}
