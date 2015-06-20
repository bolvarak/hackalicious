<?hh

/**
 * This method checks an array to see if it is associative or numerically indexed
 * @name array_is_associative()
 * @param array<mixed> $arrTest
 * @return bool
 */
function array_is_associative(array<mixed, mixed> $arrTest) : bool
{
	// Return the associative status
	return (bool) count(array_filter(array_keys($arrTest), 'is_string'));
}
