/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Thursday, October 12, 2017 - 11:11:30
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labtransformations/cubeanimator.h>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo CubeAnimator::processorInfo_
{
    "org.inviwo.CubeAnimator",      // Class identifier
    "Cube Animator",                // Display name
    "VisGra",                 // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo CubeAnimator::getProcessorInfo() const
{
    return processorInfo_;
}


CubeAnimator::CubeAnimator()
    :Processor()
    // Ports
    , meshIn_("meshIn")
    , meshOut_("meshOut")
    // Properties 
    // For a FloatProperty 
    // variablename(identifier, display name, init value, minvalue, maxvalue)
    , radius_("radius", "Radius", 4, 1, 8)
	, swinging_frequency_("swinging_frequency_", "Swinging Frequency", 8, 0, 10)
	, swinging_magnitude_("swinging_magnitude_", "Swinging Magnitude", 1, 0, 5)
	, animation_cycle_("animation_cycle_", "Animation Cycle", 0, 0, 1)
	, rotation_angle_("rotation_angle_", "Rotation Angle", 0, 0, 6.283185307)
	, swinging_cycle_position("swinging_cycle_position", "Swinging Cycle", 0, -1, 1)
{
    // Add ports
    addPort(meshIn_);
    addPort(meshOut_);
    
    // Add properties
    addProperty(radius_);
	addProperty(swinging_frequency_);
	addProperty(swinging_magnitude_);
	addProperty(animation_cycle_);
	addProperty(rotation_angle_);
	addProperty(swinging_cycle_position);

}


void CubeAnimator::process()
{
    // Clone the input mesh
    if (!meshIn_.getData()) return;
    auto mesh = meshIn_.getData()->clone();

    // Get the matrix that defines where the mesh is currently
    auto matrix = mesh->getWorldMatrix();

    // Transform the mesh (TODO)
	// REMEMBER TO PUT THE MATRICES IN THE CORRECT ORDER (WASTED HOURS ON THAT...)
	rotation_angle_ = animation_cycle_ * 6.283185307; // current cycle position (between 0-1) * 2pi
	swinging_cycle_position = swinging_magnitude_ * ::sin(rotation_angle_ * swinging_frequency_); //swinging_frequency = number of swings per circle
	matrix = glm::translate(vec3(radius_.get(), 0, 0)) * matrix;
	matrix = glm::translate(vec3(swinging_cycle_position, 0, 0)) * matrix;
	matrix = glm::rotate(rotation_angle_.get(), vec3(0, 0, 1)) * matrix;

    // Update
    mesh->setWorldMatrix(matrix);
	
    // Set output
    meshOut_.setData(mesh);
}

} // namespace