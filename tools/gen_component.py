import sys

input_vars = []
if(len(sys.argv) < 2):
    print("Usage: python3 tools/gen_component.py \"<component_name> <var_type> <var_name> <var_type> <var_name> ...\"")
    exit(1)

argv = sys.argv[1]
argv = argv.split()
component_name = argv[0]
component_name_first_lowercase = component_name[0].lower() + component_name[1:]

var = argv[1:]
for t, name in zip(*[iter(var)]*2, strict=True):
    input_vars.append([t, name])

def vars_to_constructor():
    constructor = ", ".join([x[0] + " " + x[1] for x in input_vars])
    initializer_list = ", ".join([f"{name}({name})" for _, name in input_vars])
    return f"{component_name}({constructor}) : {initializer_list}{{}};"

def vars_to_json_constructor():
    initializer_list = ", ".join([f"{name}(j[\"{component_name_first_lowercase}\"][\"{name}\"])" for _, name in input_vars])
    return f"{component_name}(json j) : {initializer_list}{{}};"

def vars_to_serialized_json():
    body = ", ".join([f"{{\"{name}\", {name}}}" for _, name in input_vars])
    body_surrounded = f"{{{body}}}"
    print(body_surrounded)
    return f"\"{component_name_first_lowercase}\", {body_surrounded}"

def vars_to_description():
    vars = " << \", ".join([f"{name}: \" << {name}" for _, name in input_vars])
    return f"\"{component_name.upper()} | {vars}"

def vars_to_members():
    return "\n    ".join([f"{var_type} {name};" for var_type, name in input_vars])


to_print = f"""
struct {component_name}: public Component {{
    {vars_to_constructor()}
    {vars_to_json_constructor()}
    json serialize() override {{
        return json{{{{{vars_to_serialized_json()}}}}};
    }}
    std::string getDescription() override {{
      return (std::stringstream() << {vars_to_description()}).str();
    }}
    inline static int id = -1;
    inline static std::string componentName = "{component_name}";
    {vars_to_members()}
}}
"""
print(to_print)