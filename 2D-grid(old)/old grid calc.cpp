struct point {
	float x, y;
};

//move theese values to somwhere local along with the update_pos
int k = 0;
int o = 0;
float size = 16;

// Add rotation of grid around middle.               (square_count.x + square_count.y)
//			      square_size * (-----------------   ------------------) or something
//                                                                               (            2            2            ) hover over the function!
void grid(
	std::vector<std::pair<point, point>>& gridlines, 
	std::vector<std::pair<point, point>>& square_vector)
{
	const float square_size = size;
	
	 
	constexpr point square_count = {40,80};
	

	std::pair<point, point> square_matrix = { { 2.0f ,-1.5  }
											 ,{ 2 , 3.0f } };
	//optimize the vector objects
	gridlines.clear();
	square_vector.clear();

	square_vector.reserve(2);
	square_vector.emplace_back(square_matrix);
	gridlines.reserve(square_count.x * square_count.y); // this could need improvment


	
	//move out to inner function maybe
	for (const auto& v : square_vector)
	{
		point origo = {k,o};
		for (int j = 0; j < square_count.y; j++) {

		
		for (int i = 0; i < square_count.x; i++) {


			float Px = origo.x + (i * square_size);
			float Py = origo.y + (j * square_size);

			float sheer_y = v.first.y * (Py);
			float sheer_x = v.second.x * (Px);


			point start = { 
				(Px * v.first.x) + (Py * v.second.x) + sheer_x, 
				(Px * v.first.y ) + (Py * v.second.y ) + sheer_y 
			};

			point end1 = { 
				start.x + square_size*v.second.x  ,
				start.y +  square_size * (v.second.y+v.first.y)};

			point end2 = { 
				start.x + square_size * (v.first.x+v.second.x), 
				start.y + square_size * v.first.y};

			gridlines.emplace_back(start, end1);
			gridlines.emplace_back(start, end2);
		}

	}
	}
	


	return;
}