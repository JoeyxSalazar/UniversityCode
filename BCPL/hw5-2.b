import "io"

static {list_of_chunks, list_idx}

let compare(in, end) be 
{
    let i =0; let bool = 1;
    if strlen(in) - strlen(end) /= 0 then
        resultis 0;
    while true do
    {
        if byte i of in /= byte i of end then
        {
            bool := 0;
            break;
        }
        if byte i of in = 0 then
            break;
        i := i + 1;
    }
    resultis bool;
   
}

let strncpy(dst, src, n) be

{ 
   for i = 0 to n - 1 do
  { let c = byte i of src;
    byte i of dst := c;

    if c = 0 then
      return }
  byte (n) of dst := 0 
}



manifest 
{
    node_str =0,
    node_nxt = 1,
    sizeof_node = 2
}

let insert_chunk(list, node) be
{
    switchon list into
    {
        case nil: 
            resultis node;
        endcase;
        default:
            list ! node_nxt := insert_chunk(list ! node_nxt, node);
    }

    resultis list;
}

let get_size_of_string(in) be
{
    let size;
    size := strlen(in) / 4;
    if strlen(in) rem 4 /= 0 then size +:= 1;
    if strlen(in) = 4 then size := 2;
    resultis size;
}

let printlist(head) be
{
    let size;
    if head = nil then return;
    size := strlen(head ! node_str) / 4;
    if strlen(head ! node_str) rem 4 /= 0 then size +:= 1;
    if strlen(head ! node_str) = 4 then size := 2;
    out("Link = 0x%x, Str = 0x%x, =%s\n", head, head ! node_str, head ! node_str);
    printlist(head ! node_nxt);
}

let my_freevec(node) be //node is a full node
{
    let offset = get_size_of_string(node ! node_str);
    node ! node_nxt := nil; 
    list_of_chunks := insert_chunk(list_of_chunks, node);
}

let remove(head, str) be
{
    let tmp; let prev;
    tmp := head; prev := nil;

    test (tmp /= nil /\ compare(str, tmp ! node_str) = 1) then          //if the head has the string
    {
        head := tmp ! node_nxt;
        //my_freevec(tmp ! (node_str)); 
        my_freevec(tmp);
        resultis head;
    }
    else 
    {
        while(tmp /= nil /\ compare(tmp ! node_str, str) = 0) do       //find the node with the string
        {
            prev := tmp;
            tmp := tmp ! node_nxt;
        }
        if(tmp = nil) then                      //the string DNE in the list
            resultis head;
        prev ! node_nxt := tmp ! node_nxt;      //previous points to two nodes ahead
        my_freevec(tmp);                //free the found string
        //freevec(tmp);                           //free the node
        resultis head;
    }
    resultis head;
}

let removechunk(head, str) be
{
    let tmp; let prev;
    tmp := head; prev := nil;

    test (tmp /= nil /\ compare(str, tmp ! node_str) = 1) then          //if the head has the string
    {
        head := tmp ! node_nxt;
        freevec(tmp);
        freevec(tmp ! node_str);
        freevec(tmp ! node_nxt);
        resultis head;
    }
    else 
    {
        while(tmp /= nil /\ compare(tmp ! node_str, str) = 0) do       //find the node with the string
        {
            prev := tmp;
            tmp := tmp ! node_nxt;
        }
        if(tmp = nil) then                      //the string DNE in the list
            resultis head;
        prev ! node_nxt := tmp ! node_nxt;      //previous points to two nodes ahead
        freevec(tmp);
        freevec(tmp ! node_str);
        freevec(tmp ! node_nxt);                          //free the node
        resultis head;
    }
    resultis head;
}

let my_newvec(str_in) be
{
    let p;
    let tmp = list_of_chunks;
    if tmp = nil then {
        p := newvec(sizeof_node);
        p ! node_str := str_in;
        p ! node_nxt := nil;
        resultis p;
    }                                       //list is empty

    while tmp /= nil do{
        if strlen(str_in) <= strlen(tmp ! node_str) then {
            out("Recycling Memory Location: 0x%x\n", tmp);
            strncpy(tmp ! node_str, str_in, strlen(str_in));
            tmp ! node_nxt := nil;
            list_of_chunks := removechunk(list_of_chunks, tmp ! node_str);
            resultis tmp; // return node 
        } 
        tmp := tmp ! node_nxt;
    }
    p := newvec(sizeof_node);
    p ! node_str := str_in;
    p ! node_nxt := nil;
    resultis p;
    //here, we add to heap because no recycle available   
}


let new_node(x) be
{
    let p = my_newvec(x);
    //p ! node_str := x;
    //p ! node_nxt := nil;
    resultis p;
}

let insert(node, str) be
{
    switchon node into
    {
        case nil: 
            resultis new_node(str);
        endcase;
        default:
            node ! node_nxt := insert(node ! node_nxt, str);
    }

    resultis node;
}


let get_del(s) be
{
    let len = strlen(s) - 7; let i = 7; let str;
    len := (len / 4) + 1;
    str := newvec(len);

    while byte i of s /= 0 do
    {
        byte i-7 of str := byte i of s;
        i+:=1;
    }
    resultis str;
}

let del(comp, del) be
{
    let str;
    for i = 0 to 5 do
    {
        if(byte i of comp) /= (byte i of del) then
            resultis 0; // not delete
    }
    resultis 1; //Means delete
}

let all(comp, al) be
{
    let str;
    for i = 0 to 2 do
    {
        if(byte i of comp) /= (byte i of al) then
            resultis 0; // not all
    }
    resultis 1; //Means all
}

let mystrdup(s, length) be
{
    let newlength; let r; 
    newlength := length/4 + 1;
    r := newvec(newlength); 
    for i = 0 to newlength - 1 do
        r!i := s!i; 
    //out("%s\n",r);  
    resultis r;
}   

let string_in() be {
   let s = vec(100);
   let a = 0; let i = 0;
   while i < 399 do {
      let char = inch();
      if char = '\n' then 
         break;
      byte i of s := char;
      i +:= 1; a +:= 1;
      byte i of s := 0;
   }
   resultis mystrdup(s, i);
}



let start() be
{
    let str;
    let flag;
    let links = nil;
    let tmp;
    let heap = vec(10000);
    init(heap, 10000);
    list_of_chunks := nil;


    out("Address of heap is %x\n", @(heap));
    out("Enter the strings and deletions: \n");
    while true do
    {
        str := string_in();
        test(del(str,"DELETE") = 1) then
        {
            links := remove(links, get_del(str));
        }
        else test(all(str,"ALL") = 1) then
        {
            printlist(links);
        }
        else test(compare(str, "END") = 0) then
        {
            links := insert(links, str);
        }
        else
        {
            break;
        }
        
    }
    printlist(links); 
    freevec(links); 
}


